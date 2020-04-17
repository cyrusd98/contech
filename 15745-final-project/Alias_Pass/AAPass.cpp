#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/raw_ostream.h"
#include "AAEval.h"
#include "llvm/Analysis/AliasAnalysis.h"

#include <iostream>
#include <set>

using namespace llvm;
using namespace std;

// static cl::opt<bool> PrintAll("my-print-all-alias-modref-info", cl::ReallyHidden);

// static cl::opt<bool> PrintNoAlias("my-print-no-aliases", cl::ReallyHidden);
// static cl::opt<bool> PrintMayAlias("my-print-may-aliases", cl::ReallyHidden);
// static cl::opt<bool> PrintPartialAlias("my-print-partial-aliases", cl::ReallyHidden);
// static cl::opt<bool> PrintMustAlias("my-print-must-aliases");

// static cl::opt<bool> PrintNoModRef("my-print-no-modref", cl::ReallyHidden);
// static cl::opt<bool> PrintRef("my-print-ref", cl::ReallyHidden);
// static cl::opt<bool> PrintMod("my-print-mod", cl::ReallyHidden);
// static cl::opt<bool> PrintModRef("my-print-modref", cl::ReallyHidden);
// static cl::opt<bool> PrintMust("my-print-must", cl::ReallyHidden);
// static cl::opt<bool> PrintMustRef("my-print-mustref", cl::ReallyHidden);
// static cl::opt<bool> PrintMustMod("my-print-mustmod", cl::ReallyHidden);
// static cl::opt<bool> PrintMustModRef("my-print-mustmodref", cl::ReallyHidden);

// static cl::opt<bool> EvalAAMD("my-evaluate-aa-metadata", cl::ReallyHidden);
 
class AAPass : public FunctionPass {
    std::unique_ptr<AAEvaluator> P;
public:
    static char ID;
    AAPass() : FunctionPass(ID) { }
    ~AAPass() { }

    // We don't modify the program, so we preserve all analyses
    //Run AAResultsWrapper prior to this
    void getAnalysisUsage(AnalysisUsage &AU) const override {
        AU.addRequired<AAResultsWrapperPass>();
        AU.setPreservesAll();
    }

    //Initialise
    bool doInitialization(Module &M) override {
        errs() << "15745 Project Alias Analysis Pass\n";
        P.reset(new AAEvaluator());
        return false;
    }

    // Main run function
    bool runOnFunction(Function &F) override {
        // if (PrintMustAlias){
        //     errs() << "\n\n\n Hello \n\n\n";
        // }
        P->runInternal(F, getAnalysis<AAResultsWrapperPass>().getAAResults());
        return false;
    }

    //Invoke destructor
    bool doFinalization(Module &M) override {
        errs() << P->MustAliasPairs.size() << "\n";
        // for (auto elem : P->MustAliasPairs){
        //     errs() << *elem.first << *elem.second << "\n";
        // }
        P.reset();
        return false;
    } 
};

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char AAPass::ID = 0;
static RegisterPass<AAPass> X("my-aa-pass", "15745: Alias Analysis Detector", false, false);
