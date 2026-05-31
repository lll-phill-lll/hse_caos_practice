// cppjit.cpp — генерация C++ из AST, компиляция в .so, загрузка через dlopen.

#include "cppjit.hpp"

#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

// Рекурсивно превращаем узел AST в кусок валидного C++ кода.
// Колонки -> row[i]; сравнения -> (a<b)?1:0 (беззнаковые); min/max -> std::min/std::max.
static void genCpp(const Node* n, std::string& out) {
    char buf[64];
    auto cmp = [&](const char* op) {
        out += "((";
        genCpp(n->kids[0].get(), out);
        out += ") "; out += op; out += " (";
        genCpp(n->kids[1].get(), out);
        out += ") ? 1 : 0)";
    };
    auto bin = [&](const char* op) {
        out += "(";
        genCpp(n->kids[0].get(), out);
        out += " "; out += op; out += " ";
        genCpp(n->kids[1].get(), out);
        out += ")";
    };
    switch (n->op) {
        case Op::Num: snprintf(buf, sizeof buf, "%lluULL", (unsigned long long)n->num); out += buf; break;
        case Op::Col: snprintf(buf, sizeof buf, "row[%d]", n->col); out += buf; break;
        case Op::Neg: out += "(-("; genCpp(n->kids[0].get(), out); out += "))"; break;
        case Op::Add: bin("+"); break;
        case Op::Sub: bin("-"); break;
        case Op::Mul: bin("*"); break;
        case Op::Lt:  cmp("<");  break;
        case Op::Gt:  cmp(">");  break;
        case Op::Le:  cmp("<="); break;
        case Op::Ge:  cmp(">="); break;
        case Op::Eq:  cmp("=="); break;
        case Op::Ne:  cmp("!="); break;
        case Op::Min:
            out += "std::min<uint64_t>(";
            genCpp(n->kids[0].get(), out); out += ", ";
            genCpp(n->kids[1].get(), out); out += ")"; break;
        case Op::Max:
            out += "std::max<uint64_t>(";
            genCpp(n->kids[0].get(), out); out += ", ";
            genCpp(n->kids[1].get(), out); out += ")"; break;
        case Op::Select:
            out += "(((";
            genCpp(n->kids[0].get(), out);
            out += ") != 0) ? (";
            genCpp(n->kids[1].get(), out);
            out += ") : (";
            genCpp(n->kids[2].get(), out);
            out += "))";
            break;
    }
}

std::string CppJit::genSource(const Node* root, int numCols) {
    std::string expr;
    genCpp(root, expr);
    std::string src;
    src += "// Сгенерировано автоматически из запроса (numCols=";
    src += std::to_string(numCols);
    src += ")\n";
    src += "#include <algorithm>\n";
    src += "#include <cstdint>\n\n";
    src += "extern \"C\" uint64_t query(const uint64_t* row) {\n";
    src += "    return " + expr + ";\n";
    src += "}\n";
    return src;
}

void CppJit::writeSource(const std::string& src) {
    FILE* f = fopen(srcPath_.c_str(), "w");
    if (f) { fwrite(src.data(), 1, src.size(), f); fclose(f); }
}

bool CppJit::compileLib() {
    const char* env = std::getenv("CXX");
    std::string cxx = env ? env : "c++";
    // -O2          : то же качество оптимизаций, что у LLVM-JIT (он тоже O2);
    // -march=native: разрешить инструкции текущего CPU, как делает ORC по host —
    //   именно благодаря этому popcnt становится одной инструкцией popcnt.
    lastCmd_ = cxx + " -O2 -march=native -shared -fPIC -o " +
               soPath_ + " " + srcPath_;
    int rc = std::system(lastCmd_.c_str());
    return rc == 0;
}

RowFn CppJit::load() {
    handle_ = dlopen(soPath_.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (!handle_) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return nullptr;
    }
    dlerror();
    void* sym = dlsym(handle_, "query");
    const char* err = dlerror();
    if (err) {
        fprintf(stderr, "dlsym failed: %s\n", err);
        return nullptr;
    }
    return reinterpret_cast<RowFn>(sym);
}

CppJit::~CppJit() {
    if (handle_) dlclose(handle_);
}
