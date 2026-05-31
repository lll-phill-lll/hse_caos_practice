// jit.hpp — публичный интерфейс JIT-движка. LLVM-заголовки спрятаны в jit.cpp
// (pimpl), поэтому main.cpp о LLVM ничего не знает.

#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include "expr.hpp"

// Сигнатура скомпилированной функции: принимает указатель на строку
// (массив uint64_t длиной numCols), возвращает результат выражения.
using RowFn = uint64_t (*)(const uint64_t*);

class Jit {
public:
    Jit();
    ~Jit();

    // Включить сброс объектного файла, который сгенерирует JIT, в файл path.
    // Вызывать ДО compile(). Это ровно тот машинный код, что ORC загрузит в память.
    void dumpObjectTo(const std::string& path);

    // 1) Сгенерировать LLVM IR для выражения. Возвращает текст IR (до оптимизаций).
    std::string buildIR(const Node* root, int numCols);

    // 2) Прогнать стандартный O2-конвейер оптимизаций. Возвращает текст IR (после).
    std::string optimize();

    // 3) JIT-скомпилировать модуль и вернуть указатель на нативную функцию.
    RowFn compile();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
