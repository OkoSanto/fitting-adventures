#ifndef GSLVECTOR_H
#define GSLVECTOR_H

#include <vector>
#include <gsl/gsl_vector.h>

class GSLVector {
public:
  GSLVector(double *elements, size_t length);
  GSLVector(std::vector<double> v);
  GSLVector(double start, double end, size_t length);
  GSLVector(size_t length);
  GSLVector(const GSLVector&);
  ~GSLVector();
  const gsl_vector *getVector(void);
private:
  gsl_vector *self;
};

#endif
