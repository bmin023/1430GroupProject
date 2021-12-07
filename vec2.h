/* Author: Brendon Kofink
 *         Johann Rajadurai
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Ball Game
 * Assignment Description: user can launch balls to hit objects.
 * Due Date: 12/08/2021
 * Date Created: 10/21/2021
 * Date Last Modified: 12/03/2021
 */

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

  /*
  * description: Constructor
  * return: none
  * precondition: The user wants to create a vector
  * postcondition: A vector is created
  */
  vec2(double setX = 0, double setY = 0);
  /*
  * description: Adds two vectors together
  * return: vec2
  * precondition: other vec2 exists
  * postcondition: The two vectors are added together
  */
  vec2 add(const vec2 &) const;
  /*
  * description: Adds a vector to this vector
  * return: void
  * precondition: other vec2 exists
  * postcondition: The vector is added to this vector
  */
  void apply(const vec2 &);
  /*
  * description: multiplies a vector by a scalar
  * return: vec2
  * precondition: scalar exists
  * postcondition: The vector is multiplied by the scalar
  */
  vec2 mult(double) const;
  /*
  * description: multiplies this vector by a scalar
  * return: void
  * precondition: scalar exists
  * postcondition: The vector is multiplied by the scalar
  */
  void scale(double);

  //Tons of operators so you can do easy vector math.
  //Hopefully you remember some stuff from trig, if not,

  //Subtracting one vector from another creates a vector pointing from v1 to v2
  //Adding one vector to another creates a vector pointing from 
  //  (0,0) to v2 put on top of v1

  // -----> + ---> = -------->

  /*
  * description: Negates a vector
  * return: vec2
  * precondition: none
  * postcondition: The negated vector is returned
  */
  vec2 operator-() const;
  /*
  * description: Adds two vectors together
  * return: vec2
  * precondition: other vec2 exists
  * postcondition: The combined vector is returned
  */
  vec2 operator+(const vec2 &) const;
  /*
  * description: Adds a vector to this vector
  * return: void
  * precondition: other vec2 exists
  * postcondition: other vec2 is added to this vector
  */
  void operator+=(const vec2 &);
  /*
  * description: Subtracts two vectors
  * return: vec2
  * precondition: other vec2 exists
  * postcondition: The subtracted vector is returned
  */
  vec2 operator-(const vec2 &) const;
  /*
  * description: Subtracts a vector from this vector
  * return: void
  * precondition: other vec2 exists
  * postcondition: other vec2 is subtracted from this vector
  */
  void operator-=(const vec2 &);

  //You can't multiply or divide two vectors. That's not really a thing.
  //But you can scale it to make the arrow shorter or longer.

  /*
  * description: Multiplies a vector by a scalar
  * return: vec2
  * precondition: scalar exists
  * postcondition: The scaled vector is returned
  */
  vec2 operator*(double) const;
  /*
  * description: Multiplies this vector by a scalar
  * return: void
  * precondition: scalar exists
  * postcondition: This vector is scaled by the scalar
  */
  void operator*=(double);
  /*
  * description: Divides a vector by a scalar
  * return: vec2
  * precondition: scalar exists
  * postcondition: The scaled vector is returned
  */
  vec2 operator/(double) const;
  /*
  * description: Divides this vector by a scalar
  * return: void
  * precondition: scalar exists
  * postcondition: This vector is scaled by the scalar
  */
  void operator/=(double);

  //Distance, still copying point_t
  /*
  * description: Returns the distance between two points
  * return: double
  * precondition: two points exist
  * postcondition: The distance between the two points is returned
  */
  double distance(const vec2 &) const;
  
  //This thing has lots of fun uses. It returns a vector with the same direction,
  //but with a magnitude of one.
  /*
  * description: Returns a unit vector
  * return: vec2
  * precondition: none
  * postcondition: A unit vector is returned
  */
  vec2 normalized() const;
  
  //Can still get direction and magnitude if you like.
  
  /*
  * description: Returns the magnitude of the vector
  * return: double
  * precondition: none
  * postcondition: The magnitude of the vector is returned
  */
  double magnitude() const;
  /*
  * description: Returns the squared magnitude of the vector
  * return: double
  * precondition: none
  * postcondition: The squared magnitude of the vector is returned
  */
  double sqrMagnitude() const;
  /*
  * description: Returns the direction of the vector
  * return: double
  * precondition: none
  * postcondition: The direction of the vector is returned
  */
  double direction() const;

  /*
  * description: Creates a unit vector pointing in a direction
  * return: vec2
  * precondition: angle is in radians
  * postcondition: A unit vector is returned
  */
  static vec2 Angle(double angle);

  //Dot product. Useful for two things.
  //1. You can find out if two vectors are pointing in the same direction.
  //  This is true if the dot product is positive. If it's negative, they're not.
  //2. You can project one vector onto another. This is useful for collisions.
  /*
  * description: Returns the dot product of two vectors
  * return: double
  * precondition: two vectors exist
  * postcondition: The dot product of the two vectors is returned
  */
  double dot(const vec2 &) const;

  //LERP. Stands for linear interpolation.
  //Great for animations.
  /*
  * description: Returns a vector between two vectors
  * return: vec2
  * precondition: two vectors exist
  * postcondition: A vector between the two vectors is returned
  */
  vec2 lerp(const vec2 &, double) const;
};


//Another class. This one takes two points to make a line.
//More shape stuff really. Will help make the dream of polygons a reality.
struct Edge
{
public:
  vec2 p1;
  vec2 p2;
  /*
  * description: Constructor
  * return: none
  * precondition: the user wants to make an edge
  * postcondition: The edge is created
  */
  Edge(vec2 p1, vec2 p2);
  /*
  * description: Default constructor
  * return: none
  * precondition: the user wants to make an edge
  * postcondition: The edge is created
  */
  Edge();
  /*
  * description: Evaluates the equation of the edge at x
  * return: double
  * precondition: x is a valid value
  * postcondition: The value of the equation at x is returned
  */
  double Evaluate(double x) const;
  /*
  * description: Returns the outward normal of the edge
  * return: vec2
  * precondition: none
  * postcondition: The outward normal of the edge is returned (not normalized)
  */
  vec2 GetNormal() const;
  /*
  * description: Returns if the edges crosses a given x value
  * return: bool
  * precondition: none
  * postcondition: Returns true if the edge crosses the x value
  */
  bool ContainsX(double x) const;
};

const vec2 UP(0, -1);
const vec2 DOWN(0, 1);
const vec2 RIGHT(1, 0);
const vec2 LEFT(-1, 0);
const vec2 ZERO(0,0);
#endif // VEC2_H_INCLUDED
