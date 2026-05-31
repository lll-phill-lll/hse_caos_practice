// expr.hpp — крошечный язык выражений "запроса" и парсер из строки.
//
// Грамматика (по убыванию приоритета сверху вниз):
//   expr     := ternary
//   ternary  := compare ('?' expr ':' ternary)?      // правоассоциативный
//   compare  := add (('<'|'>'|'<='|'>='|'=='|'!=') add)?
//   add      := mul (('+'|'-') mul)*
//   mul      := unary ('*' unary)*
//   unary    := '-' unary | '+' unary | primary
//   primary  := number | column | func '(' expr ',' expr ')' | '(' expr ')'
//   column   := 'c' digits          (c0, c1, c2, ...)
//   func     := 'min' | 'max'       (две арности)
//
// Тип всех значений — uint64_t (беззнаковые). Переполнение при + - * определено
// стандартом (заворачивается по модулю 2^64), так что умножать можно свободно.
// Сравнения беззнаковые, дают 1 / 0. Тернарник: cond != 0 -> then, иначе else.
// min(a,b)/max(a,b) — беззнаковый минимум/максимум (компилируется в cmp+cmov,
// без ветвления). Деления нет (деление на 0 — SIGFPE).
//
// ВАЖНО: само выражение приходит в рантайме (из argv), поэтому компилятор
// C++ его заранее не знает — это и есть весь смысл демо.

#pragma once
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

enum class Op {
    Num, Col, Neg,
    Add, Sub, Mul,
    Lt, Gt, Le, Ge, Eq, Ne,
    Min, Max,
    Select,  // тернарник: kids[0]=cond, kids[1]=then, kids[2]=else
};

struct Node {
    Op op;
    uint64_t num = 0;   // для Num
    int col = -1;       // для Col
    std::vector<std::unique_ptr<Node>> kids;
};

using NodePtr = std::unique_ptr<Node>;

// ----------------------------- лексер -----------------------------

enum class Tok { End, Num, Col, Func, LParen, RParen, Quest, Colon, Comma,
                 Plus, Minus, Star, Lt, Gt, Le, Ge, Eq, Ne };

struct Token {
    Tok kind;
    uint64_t num = 0;   // Num
    int col = -1;       // Col
    Op func = Op::Min;  // Func
};

[[noreturn]] inline void parseError(const std::string& src, const char* msg) {
    fprintf(stderr, "parse error: %s\n  в выражении: %s\n", msg, src.c_str());
    std::exit(1);
}

inline std::vector<Token> lex(const std::string& src) {
    std::vector<Token> out;
    const char* p = src.c_str();
    auto push = [&](Tok k) { out.push_back(Token{k}); };
    while (*p) {
        if (isspace((unsigned char)*p)) { ++p; continue; }
        char c = *p;
        if (isdigit((unsigned char)c)) {
            char* end = nullptr;
            unsigned long long v = strtoull(p, &end, 10);
            Token t{Tok::Num}; t.num = (uint64_t)v; out.push_back(t); p = end; continue;
        }
        if (c == 'c' && isdigit((unsigned char)p[1])) {
            ++p; long idx = strtol(p, (char**)&p, 10);
            Token t{Tok::Col}; t.col = (int)idx; out.push_back(t); continue;
        }
        if (isalpha((unsigned char)c)) {
            const char* s = p;
            while (isalpha((unsigned char)*p)) ++p;
            std::string id(s, p - s);
            Token t{Tok::Func};
            if (id == "min") t.func = Op::Min;
            else if (id == "max") t.func = Op::Max;
            else parseError(src, ("неизвестное имя '" + id + "'").c_str());
            out.push_back(t); continue;
        }
        switch (c) {
            case '(': push(Tok::LParen); ++p; break;
            case ')': push(Tok::RParen); ++p; break;
            case '?': push(Tok::Quest);  ++p; break;
            case ':': push(Tok::Colon);  ++p; break;
            case ',': push(Tok::Comma);  ++p; break;
            case '+': push(Tok::Plus);   ++p; break;
            case '-': push(Tok::Minus);  ++p; break;
            case '*': push(Tok::Star);   ++p; break;
            case '<': if (p[1]=='=') { push(Tok::Le); p+=2; } else { push(Tok::Lt); ++p; } break;
            case '>': if (p[1]=='=') { push(Tok::Ge); p+=2; } else { push(Tok::Gt); ++p; } break;
            case '=': if (p[1]=='=') { push(Tok::Eq); p+=2; } else parseError(src, "ожидалось '=='"); break;
            case '!': if (p[1]=='=') { push(Tok::Ne); p+=2; } else parseError(src, "ожидалось '!='"); break;
            default:  parseError(src, "неожиданный символ");
        }
    }
    push(Tok::End);
    return out;
}

// ----------------------------- парсер -----------------------------

class Parser {
public:
    Parser(const std::string& src) : src_(src), toks_(lex(src)) {}

    NodePtr parse(int& numCols) {
        NodePtr n = ternary();
        if (cur().kind != Tok::End) parseError(src_, "лишние символы в конце");
        numCols = maxCol_ + 1;   // сколько колонок реально используется
        return n;
    }

private:
    const Token& cur() const { return toks_[pos_]; }
    const Token& eat() { return toks_[pos_++]; }
    bool accept(Tok k) { if (cur().kind == k) { ++pos_; return true; } return false; }

    static NodePtr make(Op op) { auto n = std::make_unique<Node>(); n->op = op; return n; }
    static NodePtr bin(Op op, NodePtr a, NodePtr b) {
        auto n = make(op); n->kids.push_back(std::move(a)); n->kids.push_back(std::move(b)); return n;
    }

    NodePtr ternary() {
        NodePtr cond = compare();
        if (accept(Tok::Quest)) {
            NodePtr a = ternary();
            if (!accept(Tok::Colon)) parseError(src_, "ожидалось ':' в тернарнике");
            NodePtr b = ternary();
            auto n = make(Op::Select);
            n->kids.push_back(std::move(cond));
            n->kids.push_back(std::move(a));
            n->kids.push_back(std::move(b));
            return n;
        }
        return cond;
    }

    NodePtr compare() {
        NodePtr a = add();
        Op op;
        switch (cur().kind) {
            case Tok::Lt: op = Op::Lt; break;
            case Tok::Gt: op = Op::Gt; break;
            case Tok::Le: op = Op::Le; break;
            case Tok::Ge: op = Op::Ge; break;
            case Tok::Eq: op = Op::Eq; break;
            case Tok::Ne: op = Op::Ne; break;
            default: return a;
        }
        ++pos_;
        return bin(op, std::move(a), add());
    }

    NodePtr add() {
        NodePtr a = mul();
        for (;;) {
            if (accept(Tok::Plus))       a = bin(Op::Add, std::move(a), mul());
            else if (accept(Tok::Minus)) a = bin(Op::Sub, std::move(a), mul());
            else return a;
        }
    }

    NodePtr mul() {
        NodePtr a = unary();
        while (accept(Tok::Star)) a = bin(Op::Mul, std::move(a), unary());
        return a;
    }

    NodePtr unary() {
        if (accept(Tok::Minus)) { auto n = make(Op::Neg); n->kids.push_back(unary()); return n; }
        if (accept(Tok::Plus))  return unary();
        return primary();
    }

    NodePtr primary() {
        const Token& t = cur();
        if (t.kind == Tok::Num)  { ++pos_; auto n = make(Op::Num); n->num = t.num; return n; }
        if (t.kind == Tok::Col)  {
            ++pos_; auto n = make(Op::Col); n->col = t.col;
            if (t.col > maxCol_) maxCol_ = t.col;
            return n;
        }
        if (t.kind == Tok::Func) {
            Op fop = t.func; ++pos_;
            if (!accept(Tok::LParen)) parseError(src_, "ожидалась '(' после функции");
            NodePtr a = ternary();
            if (!accept(Tok::Comma)) parseError(src_, "ожидалась ',' между аргументами функции");
            NodePtr b = ternary();
            if (!accept(Tok::RParen)) parseError(src_, "ожидалась ')'");
            return bin(fop, std::move(a), std::move(b));
        }
        if (accept(Tok::LParen)) {
            NodePtr n = ternary();
            if (!accept(Tok::RParen)) parseError(src_, "ожидалась ')'");
            return n;
        }
        parseError(src_, "ожидалось число, колонка cN или '('");
    }

    std::string src_;
    std::vector<Token> toks_;
    size_t pos_ = 0;
    int maxCol_ = -1;
};

inline NodePtr parseExpr(const std::string& src, int& numCols) {
    Parser p(src);
    return p.parse(numCols);
}

// --------------------- печать разобранного AST ---------------------

inline const char* opName(Op op) {
    switch (op) {
        case Op::Num: return "Num";   case Op::Col: return "Col";
        case Op::Neg: return "Neg";   case Op::Add: return "Add";
        case Op::Sub: return "Sub";   case Op::Mul: return "Mul";
        case Op::Lt:  return "Lt";
        case Op::Gt:  return "Gt";    case Op::Le:  return "Le";
        case Op::Ge:  return "Ge";    case Op::Eq:  return "Eq";
        case Op::Ne:  return "Ne";    case Op::Min: return "Min";
        case Op::Max: return "Max";   case Op::Select: return "Select";
    }
    return "?";
}

inline const char* opSymbol(Op op) {
    switch (op) {
        case Op::Add: return "+"; case Op::Sub: return "-";
        case Op::Mul: return "*";
        case Op::Lt:  return "<"; case Op::Gt:  return ">";
        case Op::Le:  return "<="; case Op::Ge: return ">=";
        case Op::Eq:  return "=="; case Op::Ne: return "!=";
        default: return "?";
    }
}

// Структурное дерево с отступами — наглядно показывает, как парсер разложил
// приоритеты операций и ассоциативность.
inline void dumpAstNode(const Node* n, std::string& out, const std::string& prefix, bool last, bool root) {
    out += prefix;
    if (!root) out += (last ? "\u2514\u2500 " : "\u251c\u2500 ");
    char buf[64];
    switch (n->op) {
        case Op::Num: snprintf(buf, sizeof buf, "Num %llu", (unsigned long long)n->num); out += buf; break;
        case Op::Col: snprintf(buf, sizeof buf, "Col c%d", n->col); out += buf; break;
        default:      out += opName(n->op); break;
    }
    out += "\n";
    std::string childPrefix = root ? "" : prefix + (last ? "   " : "\u2502  ");
    for (size_t i = 0; i < n->kids.size(); ++i)
        dumpAstNode(n->kids[i].get(), out, childPrefix, i + 1 == n->kids.size(), false);
}

inline void dumpAstTree(const Node* n, std::string& out) {
    dumpAstNode(n, out, "", true, true);
}

// Нормализованная инфиксная запись со всеми скобками — видно фактический разбор.
inline void astToString(const Node* n, std::string& out) {
    char buf[64];
    switch (n->op) {
        case Op::Num: snprintf(buf, sizeof buf, "%llu", (unsigned long long)n->num); out += buf; break;
        case Op::Col: snprintf(buf, sizeof buf, "c%d", n->col); out += buf; break;
        case Op::Neg: out += "(-"; astToString(n->kids[0].get(), out); out += ")"; break;
        case Op::Min:
            out += "min("; astToString(n->kids[0].get(), out); out += ", ";
            astToString(n->kids[1].get(), out); out += ")"; break;
        case Op::Max:
            out += "max("; astToString(n->kids[0].get(), out); out += ", ";
            astToString(n->kids[1].get(), out); out += ")"; break;
        case Op::Select:
            out += "(";
            astToString(n->kids[0].get(), out); out += " ? ";
            astToString(n->kids[1].get(), out); out += " : ";
            astToString(n->kids[2].get(), out); out += ")";
            break;
        default:  // бинарные
            out += "(";
            astToString(n->kids[0].get(), out);
            out += " "; out += opSymbol(n->op); out += " ";
            astToString(n->kids[1].get(), out);
            out += ")";
            break;
    }
}
