#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include "vec2.h"
#include "color.h"
#include "SDL_Plotter.h"
#include <vector>

enum ShapeType
{
  CIRCLE,
  RECTANGLE
};

//Shape Class - David
// (Obviously change out my documentation for your own once you've implemented)
class Shape
{
private:
  ShapeType type;
  Color color = RED;
  vec2 size;

public:
  Shape(ShapeType type, vec2 size, Color color);
  Shape(ShapeType type, vec2 size);
  //Almost all of these will differ based on the shape type.
  //So each will have some sort of if(type==CIRCLE) statement.
  void draw(SDL_Plotter &g, vec2 pos);
  //isColliding will be called by the GO. 
  bool isColliding(Shape &other);
  //Get Projection is where magic happens. Given an axis,
  // it will return itself squished onto that axis as a minimum
  // and a maximum.
  // That's just the dot product of each corner for squares,
  // and the dot product of the center + or - the radius for circles.
  void getProjection(vec2 axis, int &min, int &max);

  // Getters
  ShapeType getType();
  vec2 getSize();
  Color getColor();

  // Setters
  void setColor(Color color);
  void setSize(vec2 size);
  void setType(ShapeType type);
};

#endif // SHAPE_H_INCLUDED