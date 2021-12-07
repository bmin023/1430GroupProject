/* Author: Brendon Kofink
 *         Johann Rajadurai
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Ball Game
 * Assignment Description: user can launch balls to hit objects.
 * Due Date: 12/08/2021
 * Date Created: 11/02/2021
 * Date Last Modified: 12/04/2021
 */

#ifndef GO_H_INCLUDED
#define GO_H_INCLUDED

#include "vec2.h"
#include "Shape.h"
#include "SDL_Plotter.h"

struct Physics
{
  Physics(){}
  Physics(vec2 velocity, double bounce, double mass, bool canCollide) {
    this->velocity = velocity;
    this->bounce = bounce;
    this->mass = mass;
    this->canCollide = canCollide;
  }
  vec2 velocity = vec2(0, 0);
  double bounce = 1.0;
  double mass = 1.0;
  bool canCollide = true;
};

enum MoveMethod
{
  PHYSICS,
  LINEAR,
  EASE
};

class GO
{
private:
  vec2 center;
  vec2 destination;
  Physics physics;
  Shape shape;
  MoveMethod moveMethod;
  double scaleChange = 1.0;
  bool moving = false;
  bool colliding = false;
  bool visible = true;
  double angle = 0;

  // To move the object by a certain amount every frame, multiply the
  // amount by deltatime for proper physics. Time component in
  // position = position + velocity*time 
  double deltaTime = 1;

  //***********************************************************************
  // description: actually calculates the velocity based on collision     *
  // return: void                                                         *
  // precondition: object is colliding                                    *
  // postcondition: object's velocity is updated                          *
  //***********************************************************************
  void Collide(GO &other);

public:
  //Constructor
  //************************************************************
  // description: constructor for game object                  *
  // return: none                                              *
  // precondition: none                                        *
  // postcondition: game object constructed with vec2 center   *
  //                and Shape shape                            *
  //                                                           *
  //************************************************************
  GO(vec2 center, Shape shape);
  
  //************************************************************
  // description: Sets the points for shape                    *
  // return: void                                              *
  // precondition: none                                        *
  // postcondition: Pointer is now set                         *
  //                                                           *
  //************************************************************
  void Init();
  
  //Setter Functions
  //************************************************************
  // description: mutator function for deltaTime               *
  // return: void                                              *
  // precondition: game object has been constructed            *
  // postcondition: deltaTime is set to the double parameter   *
  //                                                           *
  //************************************************************
  void setDeltaTime(double deltaTime);
  
  //************************************************************
  // description: mutator function for center                  *
  // return: void                                              *
  // precondition: game object has been constructed            *
  //               valid vec2 parameter is given               *
  // postcondition: center is set to vec2 parameter            *
  //                                                           *
  //************************************************************
  void setCenter(vec2 center);
  
  //************************************************************
  // description: mutator function for physics                 *
  // return: void                                              *
  // precondition: game object has been constructed            *
  //               valid Physics parameter is given            *
  // postcondition: physics is set to Physics parameter        *
  //                                                           *
  //************************************************************
  void setPhysics(Physics physics);
  
  //************************************************************
  // description: mutator function for moveMethod              *
  // return: void                                              *
  // precondition: game object has been constructed            *
  //               valid MoveMethod parameter is given         *
  // postcondition: moveMethod is set to MoveMethod parameter  *
  //                                                           *
  //************************************************************
  void setMoveMethod(MoveMethod moveMethod);
  
  //************************************************************
  // description: mutator function for moving                  *
  // return: void                                              *
  // precondition: game object has been constructed            *
  // postcondition: moving is set to boolean parameter         *
  //                                                           *
  //************************************************************
  void setMoving(bool moving);
  
  //************************************************************
  // description: mutator function for visible                 *
  // return: void                                              *
  // precondition: game object has been constructed            *
  // postcondition: visible is set to boolean parameter        *
  //                                                           *
  //************************************************************
  void setVisible(bool visible);
  
  //************************************************************
  // description: mutator function for destination             *
  // return: void                                              *
  // precondition: game object has been constructed            *
  //               valid vec2 parameter is given               *
  // postcondition: destination is set to vec2 parameter       *
  //                                                           *
  //************************************************************
  void SetDest(vec2 dest);

  //Getter Fuctions
  //************************************************************
  // description: accessor function for center                 *
  // return: vec2                                              *
  // precondition: game object has been constructed            *
  // postcondition: center is returned                         *
  //                game object is unchanged                   *
  //                                                           *
  //************************************************************
  vec2 getCenter();
  
  //************************************************************
  // description: accessor function for physics                *
  // return: Physics                                           *
  // precondition: game object has been constructed            *
  //               physics has been defined for the object     *
  // postcondition: physics is returned                        *
  //                game object is unchanged                   *
  //                                                           *
  //************************************************************
  Physics getPhysics();
  
  //************************************************************
  // description: accessor function for moveMethod             *
  // return: MoveMethod                                        *
  // precondition: game object has been constructed            *
  //               moveMethod has been define for the object   *
  // postcondition: moveMethod is returned                     *
  //                game object is unchanged                   *
  //                                                           *
  //************************************************************
  MoveMethod getMoveMethod();
  
  //************************************************************
  // description: accessor function for moving                 *
  // return: bool                                              *
  // precondition: game object has been constructed            *
  // postcondition: moving is returned                         *
  //                game object is unchanged                   *
  //                                                           *
  //************************************************************
  bool isMoving();
  
  //************************************************************
  // description: accessor function for colliding              *
  // return: bool                                              *
  // precondition: game object has been constructed            *
  // postcondition: colliding is returned                      *
  //                game object is unchanged                   *
  //                                                           *
  //************************************************************
  bool isColliding();
  
  //************************************************************
  // description: accessor function for visible                *
  // return: bool                                              *
  // precondition: game object has been constructed            *
  // postcondition: visible is returned                        *
  //                game object is unchanged                   *
  //                                                           *
  //************************************************************
  bool isVisible();

  //************************************************************
  // description: translate center of object                   *
  // return: void                                              *
  // precondition: valid double x and y parameters are given   *
  // postcondition: center is moved by the given x and y amount*
  //                                                           *
  //************************************************************
  void Translate(double x, double y);
  
  //************************************************************
  // description: translate center of object                   *
  // return: void                                              *
  // precondition: valid vec2 parameter is given               *
  // postcondition: center is moved by the given vector amount *
  //                                                           *
  //************************************************************
  void Translate(vec2 delta);
  
  //************************************************************
  // description: add force to object's current velocity       *
  // return: void                                              *
  // precondition: valid vec2 parameter is given               *
  // postcondition: force is added to velocity                 *
  //                                                           *
  //************************************************************
  void ApplyForce(vec2 force);

  //************************************************************
  // description: move the object(if moving and visible) and   *
  //              draw to screen                               *
  // return: void                                              *
  // precondition: Game Object is properly initialized         *
  // postcondition: the object is moved according to its move  *
  //                method if isMoving is true                 *
  //                the object is drawn to the screen if       *
  //                isVisible is true                          *
  //                if the object moved, the previous shape is *
  //                drawn over in white                        *
  //                                                           *
  //************************************************************
  void update(SDL_Plotter& g);

  //************************************************************
  // description: erases the object from the screen            *
  // return: void                                              *
  // precondition: game object has been constructed            *
  // postcondition: object is erased from the screen           *
  //                                                           *
  //************************************************************
  void erase(SDL_Plotter& g);

  //************************************************************
  // description: Grows the object by the given amount         *
  // return: void                                              *
  // precondition: game object has been constructed            *
  // postcondition: object is grown by the given amount        *
  //                                                           *
  //************************************************************
  void Scale(double factor);

  //************************************************************
  // description: Sets the shape to the given color            *
  // return: void                                              *
  // precondition: game object has been constructed            *
  // postcondition: object's shape is set to the given color   *
  //                                                           *
  //************************************************************
  void SetColor(Color c);

  //************************************************************
  // description: rotates the object                           *
  // return: void                                              *
  // precondition: game object has been constructed            *
  // postcondition: object is rotated                          *
  //                                                           *
  //************************************************************
  void Rotate(double angle);

  //************************************************************
  // description: check for collision and apply force if       *
  //              objects are colliding                        *
  // return: void                                              *
  // precondition: game object has been constructed            *
  // postcondition: if the two objects are colliding, the      *
  //                force is applied to the object             *
  //                                                           *
  //************************************************************
  void CheckCollision(GO& other);

  //************************************************************
  // description: gets the shape of the object                 *
  // return: Shape                                             *
  // precondition: game object has been constructed            *
  // postcondition: shape is returned                          *
  //                                                           *
  //************************************************************
  Shape getShape();

};

const Physics DEFAULT_PHYSICS = Physics(ZERO, 2.5, 1, true);
const Physics NOCOLLIDE = Physics(ZERO, 0, 0, false);
#endif // GO_H_INCLUDED
