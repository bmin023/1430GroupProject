/* Author: Brendon Kofink
 *         Johann Rajadurai
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Ball Game
 * Assignment Description: user can launch balls to hit objects.
 * Due Date: 12/08/2021
 * Date Created: 11/02/2021
 * Date Last Modified: 12/03/2021
 */

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include "vec2.h"
#include "color.h"
#include "SDL_Plotter.h"
#include <vector>

const double PI = 3.1415926535;

class Shape
{
private:
  int sides; // how many sides the polygon has. If >10, assume a circle
  vec2 *center;
  Color color = RED;
  double radius;
  double angle;
  // Only generate when you have to(when sides or radius are changed).
  vector<vec2> relativeVertices;
  /*
  * description: Draws a vertical line to the screen
  * return: void
  * precondition: g exists and is a valid SDL_Plotter
  * postcondition: A vertical line is drawn to the screen
  */
  void VerticalLine(SDL_Plotter &g, int x, int y1, int y2) const;

public:
  /*
  * description: Constructor for Shape
  * return: none
  * precondition: The user wants to create a Shape
  * postcondition: A Shape is created
  */
  Shape(int sides, double radius, Color color);
  /*
  * description: Default constructor for Shape
  * return: none
  * precondition: The user wants to create a Shape
  * postcondition: A Shape is created
  */
  Shape();
  /*
  * description: Draws the shape to the screen
  * return: void
  * precondition: g exists and is a valid SDL_Plotter
  * postcondition: The shape is drawn to the screen
  */
  void draw(SDL_Plotter &g, vec2 pos) const;
  /*
  * description: Draws the shape to the screen (default center)
  * return: void
  * precondition: g exists and is a valid SDL_Plotter
  * postcondition: The shape is drawn to the screen
  */
  void draw(SDL_Plotter &g) const;
  /*
  * description: Checks if the shape is colliding with another shape
  * return: bool
  * precondition: other shape exists and has recently initialized center
  * postcondition: Returns true if the shapes are colliding
  */
  bool isColliding(const Shape &other) const;
  /*
  * description: Gets the collision axis of this shape with another shape
  * return: vec2
  * precondition: other shape exists and has recently initialized center
  * postcondition: Returns the axis of collision
  */
  vec2 getCollisionAxis(const Shape &other) const;
  
  // Given an axis, return the dot product of each corner for squares,
  // and the dot product of the center + or - the radius for circles.
  
  /*
  * description: Gets the projection of this shape onto an axis
  * return: void
  * precondition: min and max exist
  * postcondition: min and max are set to the projection
  */
  void getProjection(vec2 axis, double &min, double &max) const;

  /*
  * description: Sets the vertices of the shape to the rigth positions
  * return: void
  * precondition: The shape has changed
  * postcondition: The vertices are set to the right positions
  */
  void generateVertices();

  // Getters
  /*
  * description: Gets the color of the shape
  * return: Color
  * precondition: none
  * postcondition: The color is returned
  */
  Color getColor();
  /*
  * description: Gets the radius of the shape
  * return: double
  * precondition: none
  * postcondition: The radius is returned
  */
  double getRadius();
  /*
  * description: Gets the sides of the shape
  * return: int
  * precondition: none
  * postcondition: The sides are returned
  */
  int getSides();
  /*
  * description: Gets the angle of the shape
  * return: double
  * precondition: none
  * postcondition: The angle is returned
  */
  double getAngle();

  // Setters
  /*
  * description: Sets the color of the shape
  * return: void
  * precondition: none
  * postcondition: The color is set
  */
  void setColor(Color color);
  /*
  * description: Sets the radius of the shape
  * return: void
  * precondition: none
  * postcondition: The radius is set
  */
  void setRadius(double radius);
  /*
  * description: Sets the center of the shape
  * return: void
  * precondition: Please let this pointer be right why is it giving me
  *  so much trouble?
  * postcondition: The center is set
  */
  void setCenter(vec2*);
  /*
  * description: Sets the angle of the shape
  * return: void
  * precondition: none
  * postcondition: The angle are set
  */
  void setAngle(double angle);
  /*
  * description: Rotates the shape
  * return: void
  * precondition: none
  * postcondition: The shape is rotated
  */
  void rotate(double angle);
};

#endif // SHAPE_H_INCLUDED
