#include <iostream>

#include "GameControl.h"

//Lucy was here

int main(int argc, char** argv)
{
  int count = 0;
  bool move = false;
  srand(time(0));
  GameControl game;
  GO& box = game.Spawn(GO(vec2(300,400),Shape(10,20,RED)),1);
  box.setMoveMethod(MoveMethod::PHYSICS);
  // box.SetDest(vec2(300,700));
  game.Spawn(GO(vec2(280,700),Shape(10,20,RED)),2);
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
      box = game.Spawn(GO(vec2(300, 50), Shape(10, 20, randColor)), 1);
      move = true;
      box.setMoveMethod(MoveMethod::PHYSICS);
    }
    vector<GO>& obstacleLayer = game.GetLayer(2);
    for (int i = 0; i< obstacleLayer.size(); i++) {
      GO& obstacle = obstacleLayer.at(i);
      if(obstacle.isColliding()) {
        game.Delete(2,i);
      }
      else if(move) {
        obstacle.SetDest(vec2(obstacle.getCenter().x, obstacle.getCenter().y - 50));
      }
    }
    if(move) {
      for (int i = 0; i < rand()%4+1; i++)
      {
        GO& obj = game.Spawn(GO(vec2(rand()%SCREEN_WIDTH, SCREEN_HEIGHT+50), Shape(rand()%11, rand()%20+30, Color::HSV(rand()%361,100,100))), 2);
        obj.SetDest(vec2(obj.getCenter().x, 700));
      }
      move = false;
    }
    game.Update();
  }
  return 0;
} 