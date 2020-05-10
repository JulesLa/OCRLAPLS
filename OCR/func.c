#include "func.h"

double atanh(double a)
{
  return tanh(a);
}

double aArctanh(double a)
{
  return 1 / pow(cosh(a),2);
}

double sigm(double a)
{
  return 1 / (1 + exp(-a));
}

/*double sigmder(double a)
{
  return exp(-a) / (pow(1 - exp(-a),2));
}*/

double sigmder(double a)
{
  return sigm(a) * (1-exp(-a));
}
