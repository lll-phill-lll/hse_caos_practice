// interp.hpp — интерпретатор запроса: дерево операторов с виртуальным eval().
//
// КАНОНИЧЕСКИЙ интерпретатор (паттерн Interpreter, expression-деревья в СУБД):
// абстрактный базовый класс Operator, по подклассу на каждую операцию. Дерево
// объектов строится один раз; на каждую операцию каждой строки — виртуальный
// вызов через vtable. Цена универсальности — непрямой вызов на КАЖДЫЙ узел: его
// нельзя заинлайнить, и предсказатель переходов на нём часто промахивается.

#pragma once
#include <cstdint>
#include <cstdlib>
#include <memory>
#include "expr.hpp"

// ============== Дерево операторов с виртуальным eval() ==============
//
// Самый честный baseline: абстрактный базовый класс Operator, по подклассу
// на каждую операцию, дерево строится один раз функцией buildOperator().
// Горячий путь — root->eval(row), уходящий в цепочку виртуальных вызовов.
// Цена универсальности здесь — непрямой вызов (vtable) на КАЖДЫЙ узел: его
// нельзя заинлайнить, и предсказатель переходов на нём часто промахивается.

struct Operator {
    virtual ~Operator() = default;
    virtual uint64_t eval(const uint64_t* row) const = 0;
};

using OpPtr = std::unique_ptr<Operator>;

struct ConstOp : Operator {
    uint64_t v;
    explicit ConstOp(uint64_t v) : v(v) {}
    uint64_t eval(const uint64_t*) const override { return v; }
};

struct ColOp : Operator {
    int idx;
    explicit ColOp(int i) : idx(i) {}
    uint64_t eval(const uint64_t* row) const override { return row[idx]; }
};

struct NegOp : Operator {
    OpPtr a;
    explicit NegOp(OpPtr a) : a(std::move(a)) {}
    uint64_t eval(const uint64_t* row) const override { return -a->eval(row); }
};

// Бинарные/унарные операции параметризуем функтором — у каждого инстанса
// шаблона свой класс и своя vtable, так что switch'а в рантайме нет.
template <class F>
struct BinOp : Operator {
    OpPtr a, b;
    BinOp(OpPtr a, OpPtr b) : a(std::move(a)), b(std::move(b)) {}
    uint64_t eval(const uint64_t* row) const override { return F{}(a->eval(row), b->eval(row)); }
};

struct SelectOp : Operator {
    OpPtr c, t, e;
    SelectOp(OpPtr c, OpPtr t, OpPtr e) : c(std::move(c)), t(std::move(t)), e(std::move(e)) {}
    uint64_t eval(const uint64_t* row) const override {
        return c->eval(row) != 0 ? t->eval(row) : e->eval(row);
    }
};

struct FAdd { uint64_t operator()(uint64_t a, uint64_t b) const { return a + b; } };
struct FSub { uint64_t operator()(uint64_t a, uint64_t b) const { return a - b; } };
struct FMul { uint64_t operator()(uint64_t a, uint64_t b) const { return a * b; } };
struct FLt  { uint64_t operator()(uint64_t a, uint64_t b) const { return a <  b ? 1 : 0; } };
struct FGt  { uint64_t operator()(uint64_t a, uint64_t b) const { return a >  b ? 1 : 0; } };
struct FLe  { uint64_t operator()(uint64_t a, uint64_t b) const { return a <= b ? 1 : 0; } };
struct FGe  { uint64_t operator()(uint64_t a, uint64_t b) const { return a >= b ? 1 : 0; } };
struct FEq  { uint64_t operator()(uint64_t a, uint64_t b) const { return a == b ? 1 : 0; } };
struct FNe  { uint64_t operator()(uint64_t a, uint64_t b) const { return a != b ? 1 : 0; } };
struct FMin { uint64_t operator()(uint64_t a, uint64_t b) const { return a < b ? a : b; } };
struct FMax { uint64_t operator()(uint64_t a, uint64_t b) const { return a > b ? a : b; } };

inline OpPtr buildOperator(const Node* n) {
    auto k = [&](int i) { return buildOperator(n->kids[i].get()); };
    switch (n->op) {  // switch только при ПОСТРОЕНИИ дерева (один раз), не в eval
        case Op::Num: return std::make_unique<ConstOp>(n->num);
        case Op::Col: return std::make_unique<ColOp>(n->col);
        case Op::Neg: return std::make_unique<NegOp>(k(0));
        case Op::Add: return std::make_unique<BinOp<FAdd>>(k(0), k(1));
        case Op::Sub: return std::make_unique<BinOp<FSub>>(k(0), k(1));
        case Op::Mul: return std::make_unique<BinOp<FMul>>(k(0), k(1));
        case Op::Lt:  return std::make_unique<BinOp<FLt>>(k(0), k(1));
        case Op::Gt:  return std::make_unique<BinOp<FGt>>(k(0), k(1));
        case Op::Le:  return std::make_unique<BinOp<FLe>>(k(0), k(1));
        case Op::Ge:  return std::make_unique<BinOp<FGe>>(k(0), k(1));
        case Op::Eq:  return std::make_unique<BinOp<FEq>>(k(0), k(1));
        case Op::Ne:  return std::make_unique<BinOp<FNe>>(k(0), k(1));
        case Op::Min:    return std::make_unique<BinOp<FMin>>(k(0), k(1));
        case Op::Max:    return std::make_unique<BinOp<FMax>>(k(0), k(1));
        case Op::Select: return std::make_unique<SelectOp>(k(0), k(1), k(2));
    }
    return std::make_unique<ConstOp>(0);  // недостижимо
}
