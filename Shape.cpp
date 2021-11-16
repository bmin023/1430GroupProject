#include "Shape.h"

Shape::Shape(int sides, double radius, Color color){
  this-> sides = sides;
  this-> radius = radius;
  this-> color = color;
}
Shape::Shape(){
  this-> sides = 10;
  this-> radius = 10;
  this-> color = RED;
}
  //Almost all of these will differ based on the shape type.
  //So each will have some sort of if statement.
void Shape::draw(SDL_Plotter &g, vec2 pos) const{

}
  //isColliding will be called by the GO. 
bool Shape::isColliding(const Shape &other) const{

}
  //Get Projection is where magic happens. Given an axis,
  // it will return itself squished onto that axis as a minimum
  // and a maximum.
  // That's just the dot product of each corner for squares,
  // and the dot product of the center + or - the radius for circles.
void Shape::getProjection(vec2 axis, int &min, int &max) const{

}
void Shape::generateVertices(){
  
}

//Getters
Color Shape::getColor(){
  return color;
}
double Shape::getRadius(){
  return radius;
}

  // Setters
void Shape::setColor(Color color){
  this-> color = color;
}
void Shape::setRadius(double radius){
  this-> radius = radius;
}
void Shape::setAngle(double angle){
  this-> angle = angle;
}
void Shape::rotate(double angle){
  this-> angle+= angle;
}
