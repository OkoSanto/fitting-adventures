LDLIBS = -lgsl -lgslcblas
CXXFLAGS = -g -Wall -std=c++0x -pedantic

main: linfunction.o gslvector.o main.cpp

main.cpp: solver.h
	touch main.cpp

gslvector.o: gslvector.h
linfunction.o: linfunction.h
