LDLIBS = -lgsl -lgslcblas
CXXFLAGS = -g -Wall -std=c++0x -pedantic

main: linfunction.o solver.o gslvector.o main.cpp

solver.o: solver.h
gslvector.o: gslvector.h
linfunction.o: linfunction.h
