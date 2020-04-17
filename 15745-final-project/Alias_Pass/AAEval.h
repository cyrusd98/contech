#ifndef _ALIAS_ANALYSIS_EVALUATOR_H_
#define _ALIAS_ANALYSIS_EVALUATOR_H_
 
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include <vector>

using namespace std;

namespace llvm {
class AAResults;
class AAEvaluator : public PassInfoMixin<AAEvaluator> {
    int64_t FunctionCount;
    int64_t NoAliasCount, MayAliasCount, PartialAliasCount, MustAliasCount;
    int64_t NoModRefCount, ModCount, RefCount, ModRefCount;
    int64_t MustCount, MustRefCount, MustModCount, MustModRefCount;
 
public:
    vector<pair<Value*, Value*>> MustAliasPairs;

    AAEvaluator()
       : FunctionCount(), NoAliasCount(), MayAliasCount(), PartialAliasCount(),
         MustAliasCount(), NoModRefCount(), ModCount(), RefCount(),
         ModRefCount(), MustCount(), MustRefCount(), MustModCount(),
         MustModRefCount() {};

    ~AAEvaluator();
    
    void runInternal(Function &F, AAResults &AA);
};
}

 
#endif