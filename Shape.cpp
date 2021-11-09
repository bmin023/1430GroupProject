#include "Shape.h"

Shape::Shape(ShapeType type, vec2 size, Color color){
    this -> type = type;
    this -> size = size;
    this -> color = color;
}
Shape::Shape(ShapeType type, vec2 size){
    this -> type = type;
    this -> size = size;
}
void Shape::draw(SDL_Plotter &g){

}

  //isColliding will be called by the GO. 
bool Shape::isColliding(Shape &other){

}
  //Get Projection is where magic happens. Given an axis,
  // it will return itself squished onto that axis as a minimum
  // and a maximum.
  // That's just the dot product of each corner for squares,
  // and the dot product of the center + or - the radius for circles.
void Shape::getProjection(vec2 axis, int &min, int &max){

}

  // Getters
ShapeType Shape::getType(){
    return type;
}
vec2 Shape::getSize(){
    return size;
}
Color Shape::getColor(){
    return color;
}

  // Setters
void Shape::setColor(Color color){
    this-> color = color;
}
void Shape::setSize(vec2 size){
    this-> size = size;
}
void Shape::setType(ShapeType type){
    this -> type = type;
}