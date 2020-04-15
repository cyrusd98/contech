#ifndef _ALIAS_ANALYSIS_EVALUATOR_H_
#define _ALIAS_ANALYSIS_EVALUATOR_H_
 
 #include "llvm/IR/Function.h"
 #include "llvm/IR/PassManager.h"
 
 namespace llvm {
 class AAResults;
 
 class AAEvaluator : public PassInfoMixin<AAEvaluator> {
   int64_t FunctionCount;
   int64_t NoAliasCount, MayAliasCount, PartialAliasCount, MustAliasCount;
   int64_t NoModRefCount, ModCount, RefCount, ModRefCount;
   int64_t MustCount, MustRefCount, MustModCount, MustModRefCount;
 
 public:
   AAEvaluator()
       : FunctionCount(), NoAliasCount(), MayAliasCount(), PartialAliasCount(),
         MustAliasCount(), NoModRefCount(), ModCount(), RefCount(),
         ModRefCount(), MustCount(), MustRefCount(), MustModCount(),
         MustModRefCount() {}
   AAEvaluator(AAEvaluator &&Arg)
       : FunctionCount(Arg.FunctionCount), NoAliasCount(Arg.NoAliasCount),
         MayAliasCount(Arg.MayAliasCount),
         PartialAliasCount(Arg.PartialAliasCount),
         MustAliasCount(Arg.MustAliasCount), NoModRefCount(Arg.NoModRefCount),
         ModCount(Arg.ModCount), RefCount(Arg.RefCount),
         ModRefCount(Arg.ModRefCount), MustCount(Arg.MustCount),
         MustRefCount(Arg.MustRefCount), MustModCount(Arg.MustModCount),
         MustModRefCount(Arg.MustModRefCount) {
     Arg.FunctionCount = 0;
   }
   ~AAEvaluator();
 
   /// Run the pass over the function.
   PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

   void runInternal(Function &F, AAResults &AA);
 };
 
 /// Create a wrapper of the above for the legacy pass manager.
 FunctionPass *createAAEvalPass();
 
 }
 
 #endif
