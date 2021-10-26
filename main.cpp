#include <iostream>
#include <chrono>
#include "point.h"
#include "color.h"
#include "force.h"
#include "ball.h"
#include "SDL_Plotter.h"

int main(int argc, char** argv)
{
  SDL_Plotter g(500, 500);
  force_t a, b(5.4,PI/2);
  Ball ball;
  ball.setForce(vec2(1, 0));
  int deltaTime;
  int lastTime;
  int currentTime;
  int startTime;

  cout << a.getMagnitude() << ' ' << a.getDirection() << endl;
  cout << b.getMagnitude() << ' ' << b.getDirection() << endl;
  a.apply(b);
  cout << a.getMagnitude() << ' ' << a.getDirection() << endl;

  //To spawn a ball every second, if time(0) - now > NUM_BALLS then spawn a ball
  
  startTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
  lastTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
  while(!g.getQuit()) {
    if(g.kbhit()) {
      g.getKey();
    }
    currentTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    lastTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    deltaTime = currentTime - lastTime;

    g.update();
    ball.setColor(color_t(255,255,255));
    ball.draw(g);
    ball.applyForce(DOWN * 0.01, deltaTime);
    ball.move(deltaTime);
    ball.setColor(RED);
    ball.draw(g);
    if(ball.getCenter().y > g.getRow()-20) {
      ball.applyForce(UP*.1, deltaTime);
    }
    if(ball.getCenter().x > g.getCol()-10) {
      ball.applyForce(LEFT*.1, deltaTime);
    }
    else if (ball.getCenter().x < 10)
    {
      ball.applyForce(RIGHT*.1, deltaTime);
    }
  }
  return 0;
}
