#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <iostream>
#include <gsl/gsl_multifit_nlin.h>

#include "gslvector.h"

using std::cout; using std::endl;

template <class Function>
class Solver : public Function{
public:
  Solver(Function f);
  ~Solver();
  void init();
  void solve();
  //private:
  gsl_multifit_fdfsolver *pSolver;
  const gsl_multifit_fdfsolver_type *type;
  gsl_multifit_function_fdf gslMultifit;
};

template<class C>
void Solver<C>::solve() {
  int status=0;
  size_t iter=0;
  do {
    iter++;
    status = gsl_multifit_fdfsolver_iterate(pSolver);
    cout << "status" << gsl_strerror(status) << endl;
    if(status)
      break;
    status = gsl_multifit_test_delta(pSolver->dx, pSolver->x, 1e-4, 1e-4);
  } while ( status == GSL_CONTINUE && iter < 500);
  cout << "results" << endl
       << "a = " << gsl_vector_get(pSolver->x,1) << endl
       << "b = " << gsl_vector_get(pSolver->x,0) << endl;
}

template<class C>
int gsl_f(const gsl_vector *X, void *solver, gsl_vector *f) {
  return ((Solver<C>*)solver)->f(X, f);
}

template<class C>
int gsl_df(const gsl_vector *X, void *solver, gsl_matrix *J) { 
  return ((Solver<C>*)solver)->df(X, J);
}

template<class C>
int gsl_fdf(const gsl_vector *X, void *solver, gsl_vector *f, gsl_matrix *J) {
  Solver<C> *s=(Solver<C> *)solver;
  int rc = s->f(X,f);
  if (rc != GSL_SUCCESS) {
    return rc;
  }
  rc = s->df(X, J);
  return rc;
}

template<class C>
gsl_multifit_function_fdf get_gsl_multifit_proto() {
  gsl_multifit_function_fdf result = {
    &gsl_f<C>,
    &gsl_df<C>,
    &gsl_fdf<C>,
    0,
    0,
    NULL
  };
  return result;
}

// test: fit linear functions at 10 points with 2 params
template<class Function>
Solver<Function>::Solver(Function f) : Function(f),
                             type(gsl_multifit_fdfsolver_lmsder) {
  cout << "solver_alloc" << f.nPoints << "points, " << f.nParams << "params." << endl;
  pSolver = gsl_multifit_fdfsolver_alloc(type , f.nPoints, f.nParams);
  this->init();
}

template<class Function>
void Solver<Function>::init() {
  gslMultifit = get_gsl_multifit_proto<Function>();
  gslMultifit.n = this->nPoints;
  gslMultifit.p = this->nParams;
  gslMultifit.params = this;
  gsl_multifit_fdfsolver_set(pSolver, &gslMultifit, this->initialParams.self); // todo: initial params
}

template <class Function>
Solver<Function>::~Solver() {
  cout << "solver_free" << endl;
  gsl_multifit_fdfsolver_free(pSolver);
}

#endif
