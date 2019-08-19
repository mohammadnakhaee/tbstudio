#include "MyMatrix.h"

void Cross_Product(double a[3], double b[3], double c[3])
{
  c[0] = a[1]*b[2] - a[2]*b[1]; 
  c[1] = a[2]*b[0] - a[0]*b[2]; 
  c[2] = a[0]*b[1] - a[1]*b[0];
}

double Dot_Product(double a[3], double b[3])
{
  static double sum;
  sum = a[0]*b[0] + a[1]*b[1] + a[2]*b[2]; 
  return sum;
}
