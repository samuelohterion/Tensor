.PHONY : run

run :	Tensor
	./Tensor
	rm Tensor

Tensor: main.cpp include/codeprinter.hpp include/tensor.hpp include/term.hpp idx.o
	g++ main.cpp idx.o -o Tensor

