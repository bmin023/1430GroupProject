#include <iostream>
#include "point.h"
#include "color.h"
#include "force.h"
#include "SDL_Plotter.h"

int main(int argc, char** argv)
{
  SDL_Plotter g(500, 500);
  point_t p1, p2(5), p3(4.3, -6.2);
  color_t c1, c2(255, 255, 255);
  force_t f1, f2(10, 0);
  c1 = RED;
  while(!g.getQuit()) {
    if(g.kbhit()) {
      g.getKey();
    }
    g.update();
  }
  return 0;
}
