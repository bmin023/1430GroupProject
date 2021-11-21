#include <iostream>

#include "GameControl.h"

//Lucy was here

int main(int argc, char** argv)
{
  GameControl game;
  GO* box = game.Spawn(GO(vec2(300,300),Shape(7,20,RED)),1);
  box->setMoveMethod(MoveMethod::LINEAR);
  box->SetDest(vec2(300,500));
  while(!game.getQuit()) {
    game.Update();
  }
  return 0;
}