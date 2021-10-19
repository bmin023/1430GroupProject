#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <cmath>

struct point_t
{
  double x, y;
  point_t(double xVal = 0, double yVal = 0);
  double distance(const point_t&) const; //Neither object can be changed.
};

#endif // POINT_H_INCLUDED