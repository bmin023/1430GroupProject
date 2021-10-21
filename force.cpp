#include "force.h"


force_t::force_t(double mag, double dir)
{
  magnitude = mag;
  direction = dir;
}

void force_t::setDirection(double d) {
  direction = d;
}

void force_t::setMagnitude(double m) {
  magnitude = m;
}

double force_t::getDirection() const {
  return direction;
}

double force_t::getMagnitude() const {
  return magnitude;
}

void force_t::apply(const force_t &f)
{
  force_t r = add(f);
  magnitude = r.magnitude;
  direction = r.direction;
}
force_t force_t::add(const force_t &f) const
{
  force_t r;

  double ax, ay, bx, by;

  ax = magnitude * cos(direction);
  bx = f.magnitude * cos(f.direction);
  
  ay = magnitude * sin(direction);
  by = f.magnitude * sin(f.direction);

  r.magnitude = sqrt(pow(ax + bx, 2) + pow(ay + by, 2));
  r.direction = atan((ay - by) / (ax - bx));
  
  return r;
}
force_t force_t::operator+(const force_t &f) const
{
  return add(f);
}