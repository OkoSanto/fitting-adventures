#include "linfunction.h"
#include <cstring>
#include <iostream>

using std::vector; using std::cout; using std::endl;

LinFunction::LinFunction(const vector<double>& x, const vector<double>& y) :
  nPoints(x.size()),
  initialParams({0.,0.}),
  coords(x),
  y(y) {
}

LinFunction::LinFunction(size_t nPoints) :
  nPoints(nPoints), 
  initialParams({0., 0.}),  // todo: somehow initialize with double * to avoid unnecessary object creation ?
  coords(1.,10.,nPoints),
  y(nPoints) {
  cout << "coords.length: " << coords.self->size <<endl;
  }

void LinFunction::setY(const vector<double>& yVals) {
  memcpy(y.self->data, &yVals[0], yVals.size() * sizeof(yVals[0]));  
}

/* f = a*x_i + b, b = X[0], a=X[1] */
int LinFunction::f(const gsl_vector *X, gsl_vector *f) {
  cout <<  "LinFunction::f(" << gsl_vector_get(X,0) << "," << gsl_vector_get(X,1) << ")." << endl;
  gsl_vector_memcpy(f, coords.self); // f = x
  gsl_vector_scale(f, gsl_vector_get(X,1));
  gsl_vector_add_constant(f, gsl_vector_get(X,0));
  gsl_vector_sub(f, y.self);
  for(size_t i=0; i<nPoints; ++i) {
    cout << f->data[i] << endl;
  }
  return GSL_SUCCESS;
}

int LinFunction::df(const gsl_vector *X, gsl_matrix *J) {
  cout <<  "LinFunction::df" << endl;
  /* J_ij = df_i/dX_j. -> J_i0 = 1 J_i1 = x_i, */
  gsl_matrix_set_all(J, 1.);
  gsl_matrix_set_col(J, 1, coords.self);
  return GSL_SUCCESS;
}
