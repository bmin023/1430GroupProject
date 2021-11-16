#include "GO.h"

void GO::update(SDL_Plotter& g){}

GO::GO(vec2 center, Shape shape){
    this->center = center;
    this->shape = shape;
    physics = DEFAULT_PHYSICS;
}
void GO::setDeltaTime(int deltaTime){
    this->deltaTime = deltaTime;
}
void GO::setCenter(vec2 center){
    this->center = center;
}
void GO::setPhysics(Physics physics){
    this->physics = physics;
}
void GO::setMoveMethod(MoveMethod moveMethod){
    this->moveMethod = moveMethod;
}
void GO::setMoving(bool moving){
    this->moving = moving;
}
void GO::setVisible(bool visible){
    this->visible = visible;
}
void GO::SetDest(vec2 dest){
    destination = dest;
}

vec2 GO::getCenter(){
    return center;
}
Physics GO::getPhysics(){
    return physics;
}
MoveMethod GO::getMoveMethod(){
    return moveMethod;
}
bool GO::isMoving(){
    return moving;
}
bool GO::isColliding(){
    return colliding;
}
bool GO::isVisible(){
    return visible;
}

void GO::Translate(double x, double y){
    center.x += x;
    center.y += y;
    
}
void GO::Translate(vec2 delta){
    center += delta;
}

void GO::ApplyForce(vec2 force){
    physics.velocity += force;
}

