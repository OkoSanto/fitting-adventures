#include <iostream>

#include <cstring>
#include <vector>

#include "solver.h"
#include "linfunction.h"

using std::cout; using std::endl; using std::vector;

int main() {
  vector<double> yVals(10);
  vector<double> xVals(10);
  
  for(int i=0; i<10; ++i) {
    xVals[i] = 1. + i*(9./10.);
    //    yVals[i] = 3*xVals[i] + 5;
    yVals[i] = 7*xVals[i] -6;
  }
  Solver<LinFunction> s(LinFunction(xVals, yVals));
  s.init();
  s.solve();
  for(int i=0; i<10; ++i) {
    yVals[i] = 3*xVals[i] +5;
  }
  s.setY(yVals);
  s.init();
  s.solve();
  return 0;
}
