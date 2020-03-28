make
clang -Xclang -disable-O0-optnone -O0 -emit-llvm -c $1 -o $2.bc
#opt -mem2reg $2.bc -o $2-m2r.bc
opt -load ./FunctionInfo.so -function-info $2.bc -o out
