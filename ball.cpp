#include "ball.h"

ball_t::ball_t()
{
  color = RED;
  center = point_t(100, 50);
  vec = force_t(0, PI / 2);
  radius = 10;
}

ball_t::ball_t(point_t c, Color col, force_t v, double r)
{
  center = c;
  color = col;
  vec = v;
  radius = r;
}

void ball_t::draw(SDL_Plotter &g)
{
  double i, angle, x1, y1;

  // Only calculate half the circle
  //  and in the Draw Rect call, mirror it across the x axis.
  for (i = 90; i < 270; i += 0.1)
  {
    //Basically, using trig to avoid using distance functions whenever possible
    angle = i;
    x1 = radius * cos(angle * PI / 180);
    y1 = radius * sin(angle * PI / 180);
    int y = center.y + y1;
    for (int k = center.x + x1; k <= center.x - x1;k++) {
      if(k < g.getCol() && y < g.getRow() && k >= 0 && y >= 0) {
        g.plotPixel(k, y, color.R, color.B, color.G);
      }
    } 
  }
}

void ball_t::move()
{
  center.x += vec.getMagnitude() * cos(vec.getDirection());
  center.y += vec.getMagnitude() * sin(vec.getDirection());
}

void ball_t::applyForce(force_t force) {
  vec.apply(force);
}


Ball::Ball()
{
  color = RED;
  center = vec2(100, 50);
  vel = vec2(0, 1);
  radius = 10;
}

Ball::Ball(vec2 c, Color col, vec2 v, double r)
{
  center = c;
  color = col;
  vel = v;
  radius = r;
}

void Ball::draw(SDL_Plotter &g)
{
  double i, angle, x1, y1;

  // Only calculate half the circle
  //  and in the Draw Rect call, mirror it across the x axis.
  for (i = PI / 2; i < 3*PI/2; i += 0.1)
  {
    // Basically, using trig to avoid using distance functions whenever possible
    x1 = radius * cos(i);
    y1 = radius * sin(i);
    int y = center.y + y1;
    for (int k = center.x + x1; k <= center.x - x1; k++)
    {
      if (k < g.getCol() && y < g.getRow() && k >= 0 && y >= 0)
      {
        g.plotPixel(k, y, color.R, color.B, color.G);
      }
    }
  }
}

void Ball::move()
{
  center += vel;
}

void Ball::move(int dt)
{
  center += vel * dt;
}

void Ball::applyForce(vec2 force, int dt)
{
  vel += force * dt;
}
