#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include "vec2.h"
#include "color.h"
#include "SDL_Plotter.h"
#include <vector>

//Shape Class - David
// (Obviously change out my documentation for your own once you've implemented)
class Shape
{
private:
  //how many sides the polygon has. If above 10, assume a circle
  int sides;
  Color color = RED;
  double radius;
  double angle;
  //Only generate when you have to. Only when sides or radius are changes.
  vector<vec2> relativeVertices;

public:
  Shape(int sides, double radius, Color color);
  Shape(int sides, double radius);
  //Almost all of these will differ based on the shape type.
  //So each will have some sort of if statement.
  void draw(SDL_Plotter &g, vec2 pos) const;
  //isColliding will be called by the GO. 
  bool isColliding(const Shape &other) const;
  //Get Projection is where magic happens. Given an axis,
  // it will return itself squished onto that axis as a minimum
  // and a maximum.
  // That's just the dot product of each corner for squares,
  // and the dot product of the center + or - the radius for circles.
  void getProjection(vec2 axis, int &min, int &max) const;
  void generateVertices();

  //Getters
  Color getColor();
  double getRadius();

  // Setters
  void setColor(Color color);
  void setRadius(double radius);
  void setAngle(double angle);
  void rotate(double angle);
};

#endif // SHAPE_H_INCLUDED