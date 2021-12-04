#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <cmath>
#include <iostream>
struct  Color 
{
  int R, G, B;
  /*
  * description: Default constructor
  * return: None
  * precondition: User wants to create a color
  * postcondition: A color is created
  */
  Color() {
    R = B = G = 0;
  }
  /*
  * description: Constructor
  * return: None
  * precondition: User wants to create a color with RGB values
  * postcondition: A color is created
  */
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
  /*
  * description: Lerps between two colors
  * return: Color
  * precondition: None
  * postcondition: Returns a color lerped between two colors
  */
  static Color Lerp(Color a, Color b, float t, bool clamp = true);
  /*
  * description: Checks if two colors are equal
  * return: bool
  * precondition: None
  * postcondition: Returns true if colors are equal
  */
  bool operator==(const Color& other) const {
    return R == other.R && G == other.G && B == other.B;
  }
};

const Color RED(204, 41, 54);
const Color BLANK(47, 53, 58);
const Color NOTWHITE(239, 231, 235);

#endif // COLOR_H_INCLUDED
