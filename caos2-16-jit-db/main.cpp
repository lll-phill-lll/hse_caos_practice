#include <chrono>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <random>
#include <span>
#include <string>
#include <string_view>
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
    std::span<const uint64_t> all(data);
    size_t cols = (size_t)numCols;
    auto t0 = Clock::now();
    uint64_t acc = 0;
    for (size_t r = 0; r < rows; ++r)
        acc += eval(all.subspan(r * cols, cols));
    sumOut = acc;
    return seconds(t0, Clock::now());
}

void writeFile(std::string_view path, std::string_view s) {
    std::ofstream(std::string(path)) << s;
}

int main(int argc, char** argv) {
    size_t rows = 30'000'000;
    uint64_t seed = 42;
    std::string_view exprStr;

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];
        if (arg == "--rows" && i + 1 < argc)      rows = std::stoull(argv[++i]);
        else if (arg == "--seed" && i + 1 < argc) seed = std::stoull(argv[++i]);
        else                                      exprStr = argv[i];
    }
    if (exprStr.empty()) {
        std::cerr << std::format("usage: {} [--rows N] [--seed S] \"<expression>\"\n", argv[0]);
        return 2;
    }

    int numCols = 0;
    NodePtr ast = parseExpr(exprStr, numCols);
    if (numCols <= 0) numCols = 1;

    std::cout << std::format("expression : {}\n", exprStr);
    std::cout << std::format("rows       : {}\n", rows);
    std::cout << std::format("cols       : {}\n", numCols);
    std::cout << std::format("data       : {:.2f} GB\n\n",
                             (double)rows * numCols * sizeof(uint64_t) / 1e9);

    std::string norm, tree;
    astToString(*ast, norm);
    dumpAstTree(*ast, tree);
    std::cout << std::format("parsed     : {}\nAST:\n{}\n", norm, tree);

    std::vector<uint64_t> data((size_t)rows * numCols);
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<uint64_t> dist(0, 100);
    for (auto& x : data) x = dist(rng);

    uint64_t sumVirt = 0;
    double tVirt = 0.0;
    {
        OpPtr opTree = buildOperator(*ast);
        tVirt = runEngine([&](Row row) { return opTree->eval(row); },
                          data, rows, numCols, sumVirt);
    }

    TJit jit;
    jit.dumpObjectTo("jit_query.o");
    auto c0 = Clock::now();
    std::string irUnopt = jit.buildIR(*ast, numCols);
    auto c1 = Clock::now();
    std::string irOpt = jit.optimize();
    auto c2 = Clock::now();
    RowFn fn = jit.compile();
    auto c3 = Clock::now();

    double tBuild = seconds(c0, c1), tOpt = seconds(c1, c2);
    double tBackend = seconds(c2, c3), tCompile = seconds(c0, c3);

    uint64_t sumJit = 0;
    double tJit = runEngine([&](Row row) { return fn(row.data()); },
                            data, rows, numCols, sumJit);

    TCppJit cpp;
    std::string cppSrc = cpp.genSource(*ast, numCols);
    cpp.writeSource(cppSrc);
    auto d0 = Clock::now();
    bool cppOk = cpp.compileLib();
    auto d1 = Clock::now();
    RowFn cppFn = cppOk ? cpp.load() : nullptr;
    double tCppCompile = seconds(d0, d1);

    uint64_t sumCpp = 0;
    double tCpp = 0.0;
    if (cppFn)
        tCpp = runEngine([&](Row row) { return cppFn(row.data()); },
                         data, rows, numCols, sumCpp);

    writeFile("query.ll", irUnopt);
    writeFile("query.opt.ll", irOpt);
    std::cout << std::format("--- LLVM IR, unoptimized ---\n{}\n", irUnopt);
    std::cout << std::format("--- LLVM IR, after O2 ---\n{}\n", irOpt);
    std::cout << std::format("--- generated C++ ---\n{}\n", cppSrc);

    auto mrows = [&](double t) { return t > 0 ? (double)rows / t / 1e6 : 0.0; };

    std::cout << std::format("{:<22}{:>10}{:>11}   {}\n", "engine", "time, s", "Mrows/s", "SUM");
    std::cout << std::format("{:<22}{:>10.3f}{:>11.1f}   {}\n", "interpreter", tVirt, mrows(tVirt), sumVirt);
    std::cout << std::format("{:<22}{:>10.3f}{:>11.1f}   {}\n", "LLVM JIT", tJit, mrows(tJit), sumJit);
    if (cppFn)
        std::cout << std::format("{:<22}{:>10.3f}{:>11.1f}   {}\n", "C++ -> .so", tCpp, mrows(tCpp), sumCpp);
    else
        std::cout << "C++ -> .so            (compile failed)\n";

    std::cout << std::format("\ncompile once: LLVM JIT {:.3f} ms (build {:.3f} + opt {:.3f} + backend {:.3f})\n",
                             tCompile * 1e3, tBuild * 1e3, tOpt * 1e3, tBackend * 1e3);
    if (cppFn)
        std::cout << std::format("              C++ -> .so {:.1f} ms ({:.0f}x slower to compile)\n",
                                 tCppCompile * 1e3, tCppCompile / tCompile);

    std::string speed = std::format("speedup vs interpreter: LLVM JIT {:.1f}x", tVirt / tJit);
    if (cppFn) speed += std::format(", C++ JIT {:.1f}x", tVirt / tCpp);
    std::cout << speed << "\n";

    bool ok = (sumVirt == sumJit) && (!cppFn || sumVirt == sumCpp);
    std::cout << std::format("match: {}\n", ok ? "OK" : "MISMATCH");
    return ok ? 0 : 1;
}
