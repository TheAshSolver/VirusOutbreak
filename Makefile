OUTPUT=main.o
SRC=main.cpp node.h
$(OUTPUT): main.cpp node.h
	g++ -std=c++23 $(SRC) -o main.o