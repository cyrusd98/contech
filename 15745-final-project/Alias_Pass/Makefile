all: AAPass.so

CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -O0

%.so: %.o AAEval.o 
	$(CXX) -dylib -shared $^ -o $@
clean:
	rm -f *.o *~ *.so
