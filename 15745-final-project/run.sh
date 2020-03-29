#make
#clang -Xclang -disable-O0-optnone -O0 -emit-llvm -c $1 -o $2.bc
#opt -mem2reg $2.bc -o $2-m2r.bc
#opt -load ./LocalOpts.so -local-opts $2-m2r.bc -o out

clang -Xclang -O1 -emit-llvm -c $1.c -o $1.bc
opt -basicaa -aa-eval -globals-aa -scev-aa -loop-simplify -instnamer -print-alias-sets -indvars -simplifycfg -view-cfg $1.bc -S
