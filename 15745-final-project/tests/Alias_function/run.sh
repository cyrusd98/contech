make
clang -Xclang -O1 -emit-llvm -c $1.c -o $1.bc
#opt -mem2reg $2.bc -o $2-m2r.bc
opt -load ./AAEval.so -my-aa-eval $1.bc -o out
