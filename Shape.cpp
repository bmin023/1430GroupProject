#include "Shape.h"
#include "vec2.h"

Shape::Shape(int sides, double radius, Color color)
{
  this->sides = sides;
  this->radius = radius;
  this->color = color;
  this->angle = 0;
  generateVertices();
}
Shape::Shape()
{
  this->sides = 10;
  this->radius = 10;
  this->angle = 0;
  this->color = RED;
  generateVertices();
}

void Shape::VerticalLine(SDL_Plotter &g, int x, int y1, int y2) const
{
  if(y1>y2) {
    swap(y1,y2);
  }
  for (int y = y1; y <= y2; y++)
  {
    if (x < g.getCol() && y < g.getRow() && x >= 0 && y >= 0)
    {
      g.plotPixel(x, y, color.R, color.G, color.B);
    }
  }
}

// Almost all of these will differ based on the shape type.
// So each will have some sort of if statement.
void Shape::draw(SDL_Plotter &g, vec2 pos) const
{
  int count = 0;
  Edge e, e1, e2;
  // Circle
  if (sides >= 10)
  {
    double i, angle, x1, y1;

    // Only calculate half the circle
    //  and in the Draw Rect call, mirror it across the x axis.
    for (i = 0; i < 180; i += 0.1)
    {
      // Basically, using trig to avoid using distance functions whenever possible
      angle = i;
      x1 = radius * cos(angle * PI / 180);
      y1 = radius * sin(angle * PI / 180);
      int x = center->x + x1;
      VerticalLine(g, pos.x + x1, pos.y + y1, pos.y - y1);
    }
  }
  else
  {
    // Using relativeVertices, create a filled in polygon
    for (int x = -radius; x <= radius; x++)
    {
      count = 0;
      // Find vertices that cross this x coordinate
      for (int i = 0; i < sides; i++)
      {
        e = Edge(relativeVertices[i], relativeVertices[(i + 1) % sides]);
        if (e.ContainsX(x))
        {
          if (count == 0)
          {
            e1 = e;
          }
          else if (count == 1)
          {
            e2 = e;
          }
          count++;
        }
      }
      // Make better later
      if (count > 0)
      {
        // Draw the line between the two vertices
        if (count == 1)
        {
          VerticalLine(g, x, e1.p1.y, e1.p2.y);
        }
        else if (count == 2)
        {
          VerticalLine(g, x+pos.x, e1.Evaluate(x)+pos.y, e2.Evaluate(x)+pos.y);
        }
      }
    }
  }
}
void Shape::draw(SDL_Plotter &g) const
{
  draw(g, *center);
}
// isColliding will be called by the GO.
bool Shape::isColliding(const Shape &other) const
{
  bool isColliding = true;
  vec2 axis, otherAxis;
  double min, max, otherMin, otherMax;
  // Get the axes
  axis = getCollisionAxis(other).normalized();
  // Get the projections
  getProjection(axis, min, max);
  other.getProjection(axis, otherMin, otherMax);
  // Check if min and max overlap with otherMin and otherMax
  if (min <= otherMax && max <= otherMin)
  {
    isColliding = false;
  }
  else
  {
    otherAxis = other.getCollisionAxis(*this).normalized();
    // Get the projections
    getProjection(otherAxis, min, max);
    other.getProjection(otherAxis, otherMin, otherMax);
    // Check if min and max overlap with otherMin and otherMax
    if (min <= otherMax && max <= otherMin)
    {
      isColliding = false;
    }
  }
  return isColliding;
}

vec2 Shape::getCollisionAxis(const Shape &other) const
{
  int max;
  Edge currEdge, bestEdge;
  vec2 axis;
  if (sides >= 10)
  {
    axis = *other.center - *center;
  }
  else
  {
    int max = -100000;
    for (int i = 0; i < sides; i++)
    {
      currEdge = Edge(relativeVertices[i], relativeVertices[(i + 1) % sides]);
      if (currEdge.GetNormal().dot(*other.center - *center) > max)
      {
        max = currEdge.GetNormal().dot(*other.center - *center);
        bestEdge = currEdge;
      }
    }
    axis = bestEdge.GetNormal();
  }
  return axis;
}

// Get Projection is where magic happens. Given an axis,
//  it will return itself squished onto that axis as a minimum
//  and a maximum.
//  That's just the dot product of each corner for squares,
//  and the dot product of the center + or - the radius for circles.
//  Assume the shape is a circle if sides >= 10.
void Shape::getProjection(vec2 axis, double &min, double &max) const
{
  // If the shape is a circle, just use the center and radius.
  if (sides >= 10)
  {
    min = (*center-axis*radius).dot(axis);
    max = (*center+axis*radius).dot(axis);
  }
  else
  {
    // Otherwise, go through each vertex and find the min and max.
    min = center->dot(axis);
    max = center->dot(axis);
    for (int i = 0; i < sides; i++)
    {
      int dot = (relativeVertices[i]+*center).dot(axis);
      if (dot < min)
        min = dot;
      if (dot > max)
        max = dot;
    }
  }
}
void Shape::generateVertices()
{
  if (sides < 10)
  {
    relativeVertices.clear();
    double vertAngles = PI / sides;
    vertAngles += angle;
    for (size_t i = 0; i < sides; i++)
    {
      relativeVertices.push_back(vec2((cos(vertAngles) * radius), (sin(vertAngles) * radius)));
      vertAngles += 2 * PI / sides;
    }
  }
}

// Getters
Color Shape::getColor()
{
  return color;
}
double Shape::getRadius()
{
  return radius;
}
int Shape::getSides()
{
  return sides;
}
double Shape::getAngle()
{
  return angle;
}

// Setters
void Shape::setColor(Color color)
{
  this->color = color;
}
void Shape::setRadius(double radius)
{
  this->radius = radius;
  generateVertices();
}
void Shape::setAngle(double angle)
{
  this->angle = angle;
  generateVertices();
}
void Shape::setCenter(vec2 *center)
{
  this->center = center;
}
void Shape::rotate(double angle)
{
  this->angle += angle;
  generateVertices();
}
