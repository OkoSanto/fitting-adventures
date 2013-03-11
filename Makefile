LDLIBS = -lgsl -lgslcblas
CXXFLAGS = -g -Wall -std=c++0x -pedantic

main: solver.o vector.o main.cpp

solver.o: solver.h solver.cpp
vector.o: vector.h vector.cpp
