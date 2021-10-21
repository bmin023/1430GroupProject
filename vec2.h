#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

//We're making a vector2 to try and make physics a little easier!
#include <cmath>

class vec2
{
public:
  double x;
  double y;

  vec2(double setX=0,double setY=0);
  vec2 add(vec2) const;
  void apply(vec2);
  vec2 mult(double) const;
  void scale(double);
  vec2 operator+(vec2) const;
  void operator+=(vec2);
  vec2 operator*(double) const;
  void operator*=(double);

  double distance(vec2) const;
  double magnitude() const;
};

const vec2 UP(0, -1);
const vec2 DOWN(0, 1);
const vec2 RIGHT(1, 0);
const vec2 LEFT(-1, 0);

#endif // VEC2_H_INCLUDED