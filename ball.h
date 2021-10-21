#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <cmath>

#include "point.h"
#include "color.h"
#include "force.h"
#include "vec2.h"

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

class Ball
{
private:
  vec2 center;
  color_t color;
  vec2 vel;
  double radius;

public:
  Ball();
  Ball(vec2, color_t, vec2, double);

  vec2 getCenter() { return center; }
  void setCenter(vec2 p) { center = p; }
  color_t getColor() { return color; }
  void setColor(color_t c) { color = c; }
  vec2 getForce() { return vel; }
  void setForce(vec2 f) { vel = f; }
  double getRadius() { return radius; }
  void setRadius(double r) { radius = r; }

  void applyForce(vec2 force);
  void draw(SDL_Plotter &);
  void move();
};

#endif // BALL_H_INCLUDED