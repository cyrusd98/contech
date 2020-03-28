// 15-745 S16 Assignment 1: FunctionInfo.cpp
// Group:
////////////////////////////////////////////////////////////////////////////////

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/AliasAnalysis.h"

#include <iostream>

using namespace llvm;

namespace {
  class FunctionInfo : public FunctionPass {
  public:
    static char ID;
    FunctionInfo() : FunctionPass(ID) { }
    ~FunctionInfo() { }

    // We don't modify the program, so we preserve all analyses
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
      AU.addRequired<AAResultsWrapperPass>();
    }

    // Do some initialization
    bool doInitialization(Module &M) override {
      errs() << "15745 Function Information Pass\n"; // TODO: remove this.
      // outs() << "Name,\tArgs,\tCalls,\tBlocks,\tInsns\n";
      //for (Module::iterator F = M.begin(), FE = M.end(); F != FE; ++F) {
   }

    // Print output for each function
    bool runOnFunction(Function &F) override {
      // outs() << "name" << ",\t" << "args" << ",\t" << "calls" << ",\t" << "bbs" << ",\t" << "insts" << "\n";
          auto AA = &getAnalysis<AAResultsWrapperPass>().getAAResults();
          for (BasicBlock &BB: F ) {
              for (Instruction &I: BB) { 
                 if (I.mayReadOrWriteMemory()) {
                     outs() << I << "\n";
                     if (AA->isNoAlias(I.getOperand(0),I.getOperand(1)))
                     {
                        errs() << I.getOperand(0);
                        errs() << " and ";
                        errs() << I.getOperand(1);
                        errs() << " are NOT aliases\n";
                     }
                     else
                     {
                    	errs() << I.getOperand(0);
                    	errs() << " and ";
                    	errs() << I.getOperand(1);
                    	errs() << " are aliases of one another\n";
                    }
              	}	
              }
          }
	  return false;
      }
   }; 
}

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char FunctionInfo::ID = 0;
static RegisterPass<FunctionInfo> X("function-info", "15745: Function Information", false, false);
