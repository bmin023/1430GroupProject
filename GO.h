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
//(Get rid of my documentation once you've made the class and repalce with yours.
// This is just to help get you started.)
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

  // Quick explanation of deltatime. So if you want to move the object
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
  GO(vec2 center, Shape shape);
  //Setters

  //Set DeltaTime should be called before every update by the gamecontroller.
  //That way physics are nice and consistent.
  void setDeltaTime(double deltaTime);
  void setCenter(vec2 center);
  void setPhysics(Physics physics);
  void setMoveMethod(MoveMethod moveMethod);
  void setMoving(bool moving);
  void setVisible(bool visible);
  void SetDest(vec2 dest);

  //Getters
  vec2 getCenter();
  Physics getPhysics();
  MoveMethod getMoveMethod();
  bool isMoving();
  bool isColliding();
  bool isVisible();

  //Translate the object's center by the given amount.
  void Translate(double x, double y);
  void Translate(vec2 delta);
  
  //Add force to object's current velocity.
  //Take deltaTime into account.
  void ApplyForce(vec2 force);

  //Update should be called every frame.
  //It should move the object and draw to screen. (Only if visible) 
  void update(SDL_Plotter& g);

  //Use their shapes to check collision and apply force if they are.
  //The GameController will call this function for you if it thinks the two are colliding.
  void CheckCollision(GO& other);

};

const Physics DEFAULT_PHYSICS = Physics(ZERO, 1, 1, true);
#endif // GO_H_INCLUDED
