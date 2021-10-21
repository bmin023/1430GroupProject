#include "vec2.h"

vec2::vec2(double setX, double setY) {
  x = setX;
  y = setY;
}

vec2 vec2::add(vec2 other) const {
  return vec2(x + other.x, y + other.y);
}

vec2 vec2::operator+(vec2 other) const{
  return add(other);
}

void vec2::apply(vec2 other) {
  x += other.x;
  y += other.y;
}

void vec2::operator+=(vec2 other) {
  apply(other);
}

vec2 vec2::mult(double m) const{
  return vec2(x * m, y * m);
}

vec2 vec2::operator*(double m) const{
  return mult(m);
}

void vec2::scale(double m) {
  x *= m;
  y *= m;
}

void vec2::operator*=(double m) {
  scale(m);
}

double vec2::distance(vec2 other) const {
  return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

double vec2::magnitude() const {
  return sqrt(pow(x, 2) + pow(y, 2));
}