#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <cmath>

#include "point.h"
#include "color.h"
#include "force.h"

#include "SDL_Plotter.h"
class ball_t
{
private:
  point_t center;
  color_t color;
  force_t vec;
  double radius;

public:
  ball_t();
  ball_t(point_t, color_t, force_t, double);

  point_t getCenter() { return center; }
  void setCenter(point_t p) { center = p; }
  color_t getColor() { return color; }
  void setColor(color_t c) { color = c; }
  force_t getForce() { return vec; }
  void setForce(force_t f) { vec = f; }
  double getRadius() { return radius; }
  void setRadius(double r) { radius = r; }

  void applyForce(force_t force);
  void draw(SDL_Plotter &);
  void move();
};

#endif // BALL_H_INCLUDED