#ifndef LINFUNCTION_H
#define LINFUNCTION_H

#include <vector>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

#include "gslvector.h"

class LinFunction {
public:
  LinFunction(const std::vector<double>& X, const std::vector<double>& Y);
  LinFunction(size_t nPoints);
  int f(const gsl_vector *X, gsl_vector *f);
  int df(const gsl_vector *X, gsl_matrix *J);
  void setY(const std::vector<double>& yVals);
  size_t nPoints;
  const static size_t nParams = 2;
  //protected:
  GSLVector initialParams; // todo: better ownership?
  GSLVector coords;
  GSLVector y;
};

#endif
