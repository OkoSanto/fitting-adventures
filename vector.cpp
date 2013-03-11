#include "vector.h"

#include <cstring>

using std::vector;

Vector::Vector(double *elements, size_t length){
  self = gsl_vector_alloc(length);
  memcpy(self->data, elements, length * sizeof(*(self->data)));
}

Vector::Vector(vector<double> v) {
  self = gsl_vector_alloc(v.size());
  memcpy(self->data, &v[0], v.size() * sizeof(*(self->data)));
}

Vector::Vector(double start, double end, size_t length) {
  self = gsl_vector_alloc(length);
  double step = (end-start)/(length-1);
  for(size_t i=0; i<length; ++i) {
    self->data[i] = start + i*step;
  }
}

Vector::Vector(size_t length) {
  self = gsl_vector_alloc(length);
  gsl_vector_set_zero(self);
}

Vector::~Vector() {
  gsl_vector_free(self);
}

