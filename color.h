#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <cmath>
#include <iostream>
struct  Color 
{
  int R, G, B;
  Color() {
    R = B = G = 0;
  }
  Color(int r, int g, int b) {
    R = r;
    B = b;
    G = g;
  }
  /*
  * description: Returns a Color from HSV values
  * return: Color
  * precondition: H in range of 0-360. S and V 0-100
  * postcondition: Returns
  */
  static Color HSV(int h, int s, int v);
};

const Color RED(220, 20, 20);
const Color BLANK(51, 61, 64);

#endif // COLOR_H_INCLUDED
