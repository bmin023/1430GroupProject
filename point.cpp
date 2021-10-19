#include "point.h"

using namespace std;

point_t::point_t(double x, double y)
{
  this->x = x;
  this->y = y;
}

double point_t::distance(const point_t& other) const {
  return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}
