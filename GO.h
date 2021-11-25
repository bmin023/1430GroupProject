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

// GameObject class- Lucy
class GO
{
private:
  vec2 center;
  vec2 destination;
  Physics physics;
  Shape shape;
  MoveMethod moveMethod;
  bool moving = false;
  bool colliding = false;
  bool visible = true;

  // Quick explanation of deltatime. If you want to move the object
  // by a certain amount every frame, you would multiply the amount by
  // deltatime for proper physics. It's the time component in 
  // position = position + velocity*time 
  double deltaTime = 0;

  // Move should be called in update.
  // Depending on the moveMethod, move the object's center.
  //If it is ease or linear, check the destination and move towards it.
  //If it is physics, move the object's center according to its velocity.
  //All movements should take into account deltaTime.
  void Collide(GO &other);

public:
  //Constructor
  //************************************************************
  // description: constructor for game object                  *
  // return: none                                              *
  // precondition: none                                        *
  // postcondition: game object constructed with vec2 center   *
  //                and Shape shape
  //                                                           *
  //************************************************************
  GO(vec2 center, Shape shape);
  
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

  //Translate the object's center by the given amount.
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

  //Update should be called every frame.
  //It should move the object and draw to screen. (Only if visible)
  //************************************************************
  // description: move the object(if moving and visible) and   *
  //              draw to screen                               *
  // return: void                                              *
  // precondition: FIXME I'M NOT SURE               *
  // postcondition: the object is moved according to its move  *
  //                method if isMoving is true                 *
  //                the object is drawn to the screen if       *
  //                isVisible is true                          *
  //                if the object moved, the previous shape is *
  //                drawn over in white                        *
  //                                                           *
  //************************************************************
  void update(SDL_Plotter& g);

  //Use their shapes to check collision and apply force if they are.
  //The GameController will call this function for you if it thinks the two are colliding.
  void CheckCollision(GO& other);

};

const Physics DEFAULT_PHYSICS = Physics(ZERO, 1, 1, false);
#endif // GO_H_INCLUDED
