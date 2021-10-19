#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

struct  color_t 
{
  int R, G, B;
  color_t() {
    R = B = G = 0;
  }
  color_t(int r, int g, int b) {
    R = r;
    B = b;
    G = g;
  }
};

const color_t RED(220, 20, 20);

#endif // COLOR_H_INCLUDED