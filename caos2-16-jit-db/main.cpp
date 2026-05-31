#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>

#include "expr.hpp"
#include "interp.hpp"
#include "jit.hpp"
#include "cppjit.hpp"

using Clock = std::chrono::steady_clock;

double seconds(Clock::time_point a, Clock::time_point b) {
    return std::chrono::duration<double>(b - a).count();
}

template <class Eval>
double runEngine(Eval&& eval, const std::vector<uint64_t>& data,
                        size_t rows, int numCols, uint64_t& sumOut) {
    auto t0 = Clock::now();
    uint64_t acc = 0;
    for (size_t r = 0; r < rows; ++r)
        acc += eval(&data[r * (size_t)numCols]);
    sumOut = acc;
    return seconds(t0, Clock::now());
}

void writeFile(const char* path, const std::string& s) {
    FILE* f = fopen(path, "w");
    if (!f) return;
    fwrite(s.data(), 1, s.size(), f);
    fclose(f);
}

int main(int argc, char** argv) {
    size_t rows = 30'000'000;
    uint64_t seed = 42;
    const char* exprStr = nullptr;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--rows") && i + 1 < argc)       rows = strtoull(argv[++i], nullptr, 10);
        else if (!strcmp(argv[i], "--seed") && i + 1 < argc)  seed = strtoull(argv[++i], nullptr, 10);
        else                                                  exprStr = argv[i];
    }
    if (!exprStr) {
        fprintf(stderr, "usage: %s [--rows N] \"<expression>\"\n", argv[0]);
        return 2;
    }

    int numCols = 0;
    NodePtr ast = parseExpr(exprStr, numCols);
    if (numCols <= 0) numCols = 1;

    printf("Expression\t: %s\n", exprStr);
    printf("Строк       : %zu\n", rows);
    printf("Колонок     : %d\n", numCols);
    printf("Данные      : %.2f ГБ (uint64_t, row-major)\n",
           (double)rows * numCols * sizeof(uint64_t) / 1e9);
    printf("\n");

    // --- что выдал парсер ---
    {
        std::string norm;
        astToString(ast.get(), norm);
        std::string tree;
        dumpAstTree(ast.get(), tree);
        printf("Разбор парсером (со всеми скобками): %s\n", norm.c_str());
        printf("AST:\n%s\n", tree.c_str());
    }

    // --- генерируем данные (беззнаковые из небольшого диапазона) ---
    std::vector<uint64_t> data((size_t)rows * numCols);
    {
        std::mt19937_64 rng(seed);
        std::uniform_int_distribution<uint64_t> dist(0, 100);
        for (auto& x : data) x = dist(rng);
    }

    // =========== 1. Интерпретатор: дерево операторов с виртуальным eval() ===========
    uint64_t sumVirt = 0;
    double tVirt = 0.0;
    {
        OpPtr tree = buildOperator(ast.get());  // дерево строится один раз
        tVirt = runEngine([&](const uint64_t* row) { return tree->eval(row); },
                          data, rows, numCols, sumVirt);
    }

    // =================== 2. LLVM JIT ===================
    Jit jit;
    const char* objPath = "jit_query.o";
    jit.dumpObjectTo(objPath);
    auto c0 = Clock::now();
    std::string irUnopt = jit.buildIR(ast.get(), numCols);
    auto c1 = Clock::now();
    std::string irOpt = jit.optimize();
    auto c2 = Clock::now();
    RowFn fn = jit.compile();
    auto c3 = Clock::now();

    double tBuild = seconds(c0, c1);
    double tOpt = seconds(c1, c2);
    double tBackend = seconds(c2, c3);
    double tCompile = seconds(c0, c3);

    uint64_t sumJit = 0;
    double tJit = runEngine(fn, data, rows, numCols, sumJit);

    // =================== 3. C++ JIT (генерация .cpp -> .so -> dlopen) ===================
    CppJit cpp;
    std::string cppSrc = cpp.genSource(ast.get(), numCols);
    cpp.writeSource(cppSrc);
    auto d0 = Clock::now();
    bool cppOk = cpp.compileLib();          // форк системного компилятора
    auto d1 = Clock::now();
    RowFn cppFn = cppOk ? cpp.load() : nullptr;  // dlopen + dlsym
    auto d2 = Clock::now();

    double tCppCompile = seconds(d0, d1);
    double tCppLoad = seconds(d1, d2);

    uint64_t sumCpp = 0;
    double tCpp = 0.0;
    if (cppFn)
        tCpp = runEngine(cppFn, data, rows, numCols, sumCpp);

    // --- сгенерированный код на экран / в файлы ---
    writeFile("query.ll", irUnopt);
    writeFile("query.opt.ll", irOpt);
    printf("================= LLVM IR (до оптимизации) =================\n%s\n", irUnopt.c_str());
    printf("============== LLVM IR функции query (после O2) ==============\n%s\n", irOpt.c_str());
    printf("(полный IR сохранён в query.ll и query.opt.ll)\n\n");
    printf("============== Сгенерированный C++ (query_gen.cpp) ==============\n%s\n", cppSrc.c_str());
    printf("Команда компиляции: %s\n\n", cpp.lastCmd().c_str());

    // --- результаты ---
    auto mrows = [&](double t) { return t > 0 ? (double)rows / t / 1e6 : 0.0; };

    printf("=========================== РЕЗУЛЬТАТЫ ===========================\n");
    printf("Движок                  время, c     млн строк/с     SUM(expr)\n");
    printf("Интерпретатор (virtual) %8.3f     %9.1f     %llu\n", tVirt, mrows(tVirt), (unsigned long long)sumVirt);
    printf("LLVM JIT                %8.3f     %9.1f     %llu\n", tJit,  mrows(tJit),  (unsigned long long)sumJit);
    if (cppFn)
        printf("C++ -> .so (dlopen)     %8.3f     %9.1f     %llu\n", tCpp, mrows(tCpp), (unsigned long long)sumCpp);
    else
        printf("C++ -> .so (dlopen)     -- компиляция не удалась (нет компилятора?) --\n");
    printf("\n");
    printf("Стоимость компиляции (разово):\n");
    printf("  LLVM JIT : build IR %.3f + opt %.3f + backend %.3f = %.3f мс  (в процессе, в памяти)\n",
           tBuild * 1e3, tOpt * 1e3, tBackend * 1e3, tCompile * 1e3);
    if (cppFn) {
        printf("  C++ JIT  : компиляция %.1f + dlopen %.3f = %.1f мс  (форк компилятора + линковка)\n",
               tCppCompile * 1e3, tCppLoad * 1e3, (tCppCompile + tCppLoad) * 1e3);
        printf("  -> LLVM компилирует тот же запрос в ~%.0fx быстрее, чем системный C++\n",
               (tCppCompile + tCppLoad) / tCompile);
    }
    printf("  -> JIT окупается после ~%.0f тыс. строк (vs интерпретатор)\n",
           tCompile / ((tVirt - tJit) / (double)rows) / 1e3);
    printf("\n");
    printf("Ускорение vs интерпретатор:  LLVM JIT %.1fx", tVirt / tJit);
    if (cppFn) printf(",  C++ JIT %.1fx", tVirt / tCpp);
    printf("\n");

    // --- проверка совпадения результатов (у целых — точное равенство) ---
    bool ok = (sumVirt == sumJit);
    if (cppFn) ok = ok && (sumVirt == sumCpp);
    printf("\nСовпадение результатов: %s\n", ok ? "OK" : "РАСХОЖДЕНИЕ!");
    return ok ? 0 : 1;
}
