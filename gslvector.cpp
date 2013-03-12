#include "gslvector.h"

#include <cstring>

using std::vector;

GSLVector::GSLVector(double *elements, size_t length){
  self = gsl_vector_alloc(length);
  memcpy(self->data, elements, length * sizeof(*(self->data)));
}

GSLVector::GSLVector(vector<double> v) {
  self = gsl_vector_alloc(v.size());
  memcpy(self->data, &v[0], v.size() * sizeof(*(self->data)));
}

GSLVector::GSLVector(double start, double end, size_t length) {
  self = gsl_vector_alloc(length);
  double step = (end-start)/(length-1);
  for(size_t i=0; i<length; ++i) {
    self->data[i] = start + i*step;
  }
}

GSLVector::GSLVector(size_t length) {
  self = gsl_vector_alloc(length);
  gsl_vector_set_zero(self);
}

GSLVector::GSLVector(const GSLVector&other) {
  self = gsl_vector_alloc(other.self->size);
  gsl_vector_memcpy(self, other.self);
}

GSLVector::~GSLVector() {
  gsl_vector_free(self);
}

const gsl_vector *GSLVector::getVector() {
  return self;
}
