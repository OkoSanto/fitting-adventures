#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <gsl/gsl_vector.h>

class Vector {
public:
  Vector(double *elements, size_t length);
  Vector(std::vector<double> v);
  Vector(double start, double end, size_t length);
  Vector(size_t length);
  ~Vector();
  gsl_vector *self;
};

#endif
