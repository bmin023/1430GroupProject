#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

// We're making a 2d vector to try and make physics a little easier!
#include <cmath>

struct vec2
{
public:
  //Keeping x and y public so it has the same functionality as point_t.
  double x;
  double y;

  vec2(double setX = 0, double setY = 0);
  vec2 add(const vec2 &) const;
  void apply(const vec2 &);
  vec2 mult(double) const;
  void scale(double);

  //Tons of operators so you can do easy vector math.
  //Hopefully you remember some stuff from trig, if not,

  //Subtracting one vector from another creates a vector pointing from v1 to v2
  //Adding one vector to another creates a vector pointing from 
  //  (0,0) to v2 put on top of v1

  // -----> + ---> = -------->

  vec2 operator-() const;
  vec2 operator+(const vec2 &) const;
  void operator+=(const vec2 &);
  vec2 operator-(const vec2 &) const;
  void operator-=(const vec2 &);

  //You can't multiply or divide two vectors. That's not really a thing.
  //But you can scale it to make the arrow shorter or longer.

  vec2 operator*(double) const;
  void operator*=(double);
  vec2 operator/(double) const;
  void operator/=(double);

  //Distance, still copying point_t
  double distance(const vec2 &) const;
  
  //This thing has lots of fun uses. It returns a vector with the same direction,
  //but with a magnitude of one.
  vec2 normalized() const;
  
  //Can still get direction and magnitude if you like.
  
  double magnitude() const;
  double direction() const;
};

const vec2 UP(0, -1);
const vec2 DOWN(0, 1);
const vec2 RIGHT(1, 0);
const vec2 LEFT(-1, 0);

#endif // VEC2_H_INCLUDED