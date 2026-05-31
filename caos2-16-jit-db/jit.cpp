// jit.cpp — генерация LLVM IR из AST + ORC LLJIT.
//
// Что здесь происходит, по шагам (это и есть "от идеи JIT к применению"):
//
//   AST  --(IRBuilder)-->  LLVM IR  --(PassBuilder O2)-->  оптимизированный IR
//        --(LLJIT/ORC)-->  нативный машинный код в памяти  -->  указатель на функцию
//
// Мы строим ровно одну функцию:   i64 query(i64* row)
// где row[i] — значение i-й колонки текущей строки. Тело функции —
// прямой перевод выражения в целочисленную арифметику, без какой-либо
// диспетчеризации: то, что у интерпретатора было switch'ем в рантайме,
// здесь "вплавляется" в код один раз на этапе компиляции запроса.

#include "jit.hpp"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/Error.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/ExecutionEngine/Orc/ObjectTransformLayer.h"
#include "llvm/Support/MemoryBuffer.h"

using namespace llvm;

struct Jit::Impl {
    std::unique_ptr<orc::LLJIT> jit;
    std::unique_ptr<LLVMContext> ctx;
    std::unique_ptr<Module> mod;
    IRBuilder<>* builder = nullptr;
    Function* fn = nullptr;
    Value* rowArg = nullptr;
    int numCols = 0;

    // Рекурсивно превращаем узел AST в значение LLVM (SSA-значение типа i64).
    Value* gen(const Node* n) {
        IRBuilder<>& B = *builder;
        Type* i64 = B.getInt64Ty();

        switch (n->op) {
            case Op::Num:
                return B.getInt64((uint64_t)n->num);

            case Op::Col: {
                // row[col]:  getelementptr i64, ptr row, i64 col;  load i64
                Value* idx = B.getInt64(n->col);
                Value* ptr = B.CreateGEP(i64, rowArg, idx, "colptr");
                return B.CreateLoad(i64, ptr, "col");
            }

            case Op::Neg: return B.CreateNeg(gen(n->kids[0].get()), "neg");

            case Op::Add: return B.CreateAdd(gen(n->kids[0].get()), gen(n->kids[1].get()), "add");
            case Op::Sub: return B.CreateSub(gen(n->kids[0].get()), gen(n->kids[1].get()), "sub");
            case Op::Mul: return B.CreateMul(gen(n->kids[0].get()), gen(n->kids[1].get()), "mul");

            // Сравнения -> i1 -> i64 (zext даёт 1/0). Предикаты беззнаковые (U*).
            case Op::Lt: return cmp(CmpInst::ICMP_ULT, n);
            case Op::Gt: return cmp(CmpInst::ICMP_UGT, n);
            case Op::Le: return cmp(CmpInst::ICMP_ULE, n);
            case Op::Ge: return cmp(CmpInst::ICMP_UGE, n);
            case Op::Eq: return cmp(CmpInst::ICMP_EQ, n);
            case Op::Ne: return cmp(CmpInst::ICMP_NE, n);

            // llvm.umin/umax -> cmp + cmov (branchless) на x86.
            case Op::Min:
                return B.CreateBinaryIntrinsic(Intrinsic::umin, gen(n->kids[0].get()), gen(n->kids[1].get()));
            case Op::Max:
                return B.CreateBinaryIntrinsic(Intrinsic::umax, gen(n->kids[0].get()), gen(n->kids[1].get()));

            case Op::Select: {
                // cond != 0 ? then : else
                Value* c = gen(n->kids[0].get());
                Value* cond = B.CreateICmpNE(c, B.getInt64(0), "cond");
                Value* t = gen(n->kids[1].get());
                Value* e = gen(n->kids[2].get());
                return B.CreateSelect(cond, t, e, "sel");
            }
        }
        return B.getInt64(0);  // недостижимо
    }

    Value* cmp(CmpInst::Predicate pred, const Node* n) {
        IRBuilder<>& B = *builder;
        Value* a = gen(n->kids[0].get());
        Value* b = gen(n->kids[1].get());
        Value* i1 = B.CreateICmp(pred, a, b, "cmp");
        return B.CreateZExt(i1, B.getInt64Ty(), "toi64");
    }
};

Jit::Jit() : impl_(std::make_unique<Impl>()) {
    // Инициализация нативного бэкенда — обязательна до создания LLJIT.
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    impl_->jit = cantFail(orc::LLJITBuilder().create());
    impl_->ctx = std::make_unique<LLVMContext>();
}

Jit::~Jit() = default;

void Jit::dumpObjectTo(const std::string& path) {
    // ObjectTransformLayer вызывается с готовым объектным файлом (ELF/Mach-O),
    // который JIT уже сгенерировал, но ещё не залинковал в память. Сохраняем его
    // как есть и пропускаем дальше без изменений.
    impl_->jit->getObjTransformLayer().setTransform(
        [path](std::unique_ptr<MemoryBuffer> obj)
            -> Expected<std::unique_ptr<MemoryBuffer>> {
            std::error_code ec;
            raw_fd_ostream os(path, ec);
            if (!ec) os << obj->getBuffer();
            return obj;
        });
}

std::string Jit::buildIR(const Node* root, int numCols) {
    Impl& s = *impl_;
    s.numCols = numCols;
    s.mod = std::make_unique<Module>("query_module", *s.ctx);
    // Берём data layout у JIT, чтобы оптимизатор знал размеры/выравнивания целевой машины.
    s.mod->setDataLayout(s.jit->getDataLayout());
    s.mod->setTargetTriple(s.jit->getTargetTriple());

    IRBuilder<> builder(*s.ctx);
    s.builder = &builder;

    Type* i64 = builder.getInt64Ty();
    Type* ptr = PointerType::getUnqual(*s.ctx);  // opaque ptr (современный LLVM)
    FunctionType* fty = FunctionType::get(i64, {ptr}, /*vararg*/ false);
    s.fn = Function::Create(fty, Function::ExternalLinkage, "query", s.mod.get());
    s.rowArg = s.fn->getArg(0);
    s.rowArg->setName("row");

    BasicBlock* bb = BasicBlock::Create(*s.ctx, "entry", s.fn);
    builder.SetInsertPoint(bb);

    Value* result = s.gen(root);
    builder.CreateRet(result);

    if (verifyFunction(*s.fn, &errs())) {
        errs() << "internal error: сгенерирован некорректный IR\n";
    }

    std::string out;
    raw_string_ostream os(out);
    s.mod->print(os, nullptr);
    return out;
}

std::string Jit::optimize() {
    Impl& s = *impl_;
    PassBuilder PB;
    LoopAnalysisManager LAM;
    FunctionAnalysisManager FAM;
    CGSCCAnalysisManager CGAM;
    ModuleAnalysisManager MAM;
    PB.registerModuleAnalyses(MAM);
    PB.registerCGSCCAnalyses(CGAM);
    PB.registerFunctionAnalyses(FAM);
    PB.registerLoopAnalyses(LAM);
    PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

    ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(OptimizationLevel::O2);
    MPM.run(*s.mod, MAM);

    std::string out;
    raw_string_ostream os(out);
    s.mod->print(os, nullptr);
    return out;
}

RowFn Jit::compile() {
    Impl& s = *impl_;
    orc::ThreadSafeModule tsm(std::move(s.mod), std::move(s.ctx));
    cantFail(s.jit->addIRModule(std::move(tsm)));
    auto sym = cantFail(s.jit->lookup("query"));
    return sym.toPtr<RowFn>();
}
