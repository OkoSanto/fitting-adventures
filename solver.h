#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <gsl/gsl_multifit_nlin.h>

#include "vector.h"

class Solver {
public:
  Solver();
  ~Solver();
  int f(const gsl_vector *X, gsl_vector *f);
  void set();
  void setY(const std::vector<double>& yVals);
  void solve();
  int df(const gsl_vector *X, gsl_matrix *J);
  //private:
  gsl_multifit_fdfsolver *pSolver;
  const gsl_multifit_fdfsolver_type *type;
  size_t nPoints;
  size_t nParams;
  gsl_multifit_function_fdf gslMultifit;
  Vector initialParams; // todo: better ownership?
  Vector coords;
  Vector y;
};

#endif
