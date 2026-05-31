// cppjit.hpp — "честный" JIT через генерацию исходного C++.
//
// Идея максимально прямолинейна и не требует никакого LLVM API:
//   AST  -->  текст .cpp с функцией query()  -->  вызвать системный компилятор
//        -->  получить .so  -->  dlopen + dlsym  -->  указатель на функцию.
//
// Так делают/делали реальные системы (ранний ClickHouse, разные кодогенераторы).
// Машинный код на выходе — такой же оптимальный, как у LLVM-JIT (это тот же
// clang/gcc с -O2), НО задержка компиляции на порядки больше: вместо единиц мс
// в памяти мы форкаем целый компилятор и линкер. На лекции это ровно тот
// trade-off, из-за которого СУБД предпочитают встроенный LLVM, а не вызов g++.

#pragma once
#include <string>
#include "expr.hpp"
#include "jit.hpp"  // ради общего типа RowFn

class CppJit {
public:
    CppJit() = default;
    ~CppJit();

    // Сгенерировать текст .cpp (его же удобно показать на экране).
    std::string genSource(const Node* root, int numCols);

    // Записать исходник на диск (по умолчанию query_gen.cpp).
    void writeSource(const std::string& src);

    // Скомпилировать в разделяемую библиотеку системным компилятором.
    // Возвращает true при успехе. Команду компилятора кладёт в lastCmd().
    bool compileLib();

    // dlopen + dlsym -> указатель на нативную функцию query.
    RowFn load();

    const std::string& srcPath() const { return srcPath_; }
    const std::string& soPath()  const { return soPath_; }
    const std::string& lastCmd() const { return lastCmd_; }

private:
    std::string srcPath_ = "query_gen.cpp";
    std::string soPath_  = "./query_gen.so";
    std::string lastCmd_;
    void* handle_ = nullptr;
};
