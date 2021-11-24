#include <iostream>

#include "GameControl.h"

//Lucy was here

int main(int argc, char** argv)
{
  GameControl game;
  GO* box = game.Spawn(GO(vec2(285,670),Shape(10,20,RED)),1);
  box->setMoveMethod(MoveMethod::EASE);
  // box->SetDest(vec2(300,700));
  GO* box2 = game.Spawn(GO(vec2(300,700),Shape(3,20,RED)),2);
  while(1) {
    game.layerCollide(1, 2);
    game.Update();
  }
  return 0;
}