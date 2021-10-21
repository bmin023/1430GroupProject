#include <iostream>
#include "point.h"
#include "color.h"
#include "force.h"
#include "ball.h"
#include "SDL_Plotter.h"

int main(int argc, char** argv)
{
  SDL_Plotter g(500, 500);
  force_t a, b(5.4,PI/2);
  ball_t ball;
  ball.setForce(force_t(1, 0));

  cout << a.getMagnitude() << ' ' << a.getDirection() << endl;
  cout << b.getMagnitude() << ' ' << b.getDirection() << endl;
  a.apply(b);
  cout << a.getMagnitude() << ' ' << a.getDirection() << endl;


  while(!g.getQuit()) {
    if(g.kbhit()) {
      g.getKey();
    }
    g.update();
    ball.setColor(color_t(255,255,255));
    ball.draw(g);
    ball.applyForce(GRAVITY);
    ball.move();
    ball.setColor(RED);
    ball.draw(g);
    if(ball.getCenter().y > g.getRow()-50) {
      ball.applyForce(force_t(1, -PI / 2));
    }
    if(ball.getCenter().x > g.getCol()-10) {
      ball.applyForce(force_t(1, PI));
    }
    // else if (ball.getCenter().x < 10)
    // {
    //   ball.applyForce(force_t(1, 0));
    // }
  }
  return 0;
}
