#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

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
};

const Color RED(220, 20, 20);

#endif // COLOR_H_INCLUDED