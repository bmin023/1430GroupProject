#include <iostream>

#include "GameControl.h"

//Lucy was here

int main(int argc, char** argv)
{
  int count = 0;
  srand(time(0));
  GameControl game;
  GO& box = game.Spawn(GO(vec2(300,400),Shape(10,20,RED)),1);
  box.setMoveMethod(MoveMethod::PHYSICS);
  // box.SetDest(vec2(300,700));
  GO& box2 = game.Spawn(GO(vec2(280,700),Shape(10,20,RED)),2);
  while(1) {
    game.layerCollide(1, 2);
    if(box.getCenter().x > SCREEN_WIDTH-20) {
      box.ApplyForce(LEFT);
    }
    else if(box.getCenter().x<20) {
      box.ApplyForce(RIGHT);
    }
    if(box.getCenter().y<0) {
      box.ApplyForce(DOWN);
    }
    if(box.getCenter().y>SCREEN_HEIGHT+20) {
      game.Delete(box, 1);
      Color randColor = Color::HSV(count % 361, 70, 100);
      count += 10;
      cout << "New Color: " << randColor.R << " " << randColor.G << " " << randColor.B << endl;
      box = game.Spawn(GO(vec2(300, 400), Shape(10, 20, randColor)), 1);
      box.setMoveMethod(MoveMethod::PHYSICS);
    }
    game.Update();
  }
  return 0;
} 