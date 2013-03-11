#include "solver.h"

#include <cstring>
#include <iostream>
#include <vector>

using std::vector; using std::cout; using std::endl;

void Solver::solve() {
  int status=0;
  size_t iter=0;
  do {
    iter++;
    status = gsl_multifit_fdfsolver_iterate(pSolver);
    cout << "status" << gsl_strerror(status) << endl;
    //    print_state(iter, pSolver);
    if(status)
      break;
    status = gsl_multifit_test_delta(pSolver->dx, pSolver->x, 1e-4, 1e-4);
  } while ( status == GSL_CONTINUE && iter < 500);
  cout << "results" << endl
       << "a = " << gsl_vector_get(pSolver->x,1) << endl
       << "b = " << gsl_vector_get(pSolver->x,0) << endl;
  
}

/* f = a*x_i + b, b = X[0], a=X[1] */
int Solver::f(const gsl_vector *X, gsl_vector *f) {
  cout <<  "Solver::f" << endl;
  gsl_vector_memcpy(f, coords.self); // f = x
  gsl_vector_scale(f, gsl_vector_get(X,1));
  gsl_vector_add_constant(f, gsl_vector_get(X,0));
  gsl_vector_sub(f, y.self);
  for(size_t i=0; i<nPoints; ++i) {
    cout << f->data[i] << endl;
  }
  return GSL_SUCCESS;
}

int Solver::df(const gsl_vector *X, gsl_matrix *J) {
  cout <<  "Solver::df" << endl;
  /* J_ij = df_i/dX_j. -> J_i0 = 1 J_i1 = x_i, */
  gsl_matrix_set_all(J, 1.);
  gsl_matrix_set_col(J, 1, coords.self);
  return GSL_SUCCESS;
}

int gsl_f(const gsl_vector *X, void *solver, gsl_vector *f) {
  return ((Solver*)solver)->f(X, f);
}

int gsl_df(const gsl_vector *X, void *solver, gsl_matrix *J) { 
  return ((Solver*)solver)->df(X, J);
}

int gsl_fdf(const gsl_vector *X, void *solver, gsl_vector *f, gsl_matrix *J) {
  Solver *s=(Solver *)solver;
  int rc = s->f(X,f);
  if (rc != GSL_SUCCESS) {
    return rc;
  }
  rc = s->df(X, J);
  return rc;
}

gsl_multifit_function_fdf gsl_multifit_proto = {
  &gsl_f,
  &gsl_df,
  &gsl_fdf,
  0,
  0,
  NULL
};

// test: fit linear functions at 10 points with 2 params
Solver::Solver() : type(gsl_multifit_fdfsolver_lmsder),
                   nPoints(10),
                   nParams(2),
                   initialParams({0.,0.}),
                   coords(1.,10.,nPoints),
                   y(nPoints) { // todo: somehow initialize with double * to avoid unnecessary object creation ?
  cout << "solver_alloc" << endl;
  for (size_t i=0; i<nPoints; ++i) {
    y.self->data[i] = 5.*coords.self->data[i] + 3.;
    //    cout << yVals[i] << endl;
  }
  pSolver = gsl_multifit_fdfsolver_alloc(type , nPoints, nParams);
  this->set();
}

void Solver::set() {
  gslMultifit = gsl_multifit_proto;
  gslMultifit.n = nPoints;
  gslMultifit.p = nParams;
  gslMultifit.params = this;
  gsl_multifit_fdfsolver_set(pSolver, &gslMultifit, initialParams.self); // todo: initial params
}

void Solver::setY(const vector<double>& yVals) {
  memcpy(y.self->data, &yVals[0], yVals.size());  
}

Solver::~Solver() {
  cout << "solver_free" << endl;
  gsl_multifit_fdfsolver_free(pSolver);
}
