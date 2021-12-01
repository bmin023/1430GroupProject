#include <iostream>

#include "GameControl.h"

//Lucy was here

void setPointer(GameControl &game, double angle);

int main(int argc, char **argv)
{
  int count = 0;
  bool move = false;
  double angle = PI / 2;
  srand(time(0));
  GameControl game;
  game.Spawn(GO(TOP_CENTER, Shape(10, 5, RED)), 0);
  game.Spawn(GO(TOP_CENTER, Shape(10, 10, RED)), 0);
  setPointer(game, angle);
  while (!game.getQuit())
  {
    game.layerCollide(1, 2);
    game.Text("Score:"+to_string(count),vec2(100,100),3,3,true);
    if (game.Key(LEFT_ARROW))
    {
      angle += 0.1;
      setPointer(game, angle);
    }
    else if (game.Key(RIGHT_ARROW))
    {
      angle -= 0.1;
      setPointer(game, angle);
    }
    else if (game.KeyDown(' ')) {
      Color randColor = Color::HSV(count % 361, 70, 100);
      count += 10;
      GO& ball = game.Spawn(GO(TOP_CENTER, Shape(10, 20, randColor)), 1);
      ball.setMoveMethod(MoveMethod::PHYSICS);
      ball.ApplyForce(vec2::Angle(angle)*3);
    }
    vector<GO> &ballLayer = game.GetLayer(1);
    int ballCount = ballLayer.size();
    for (int i = 0; i < ballLayer.size();i++) {
      GO &ball = ballLayer.at(i);
      if (ball.getCenter().x > SCREEN_WIDTH - 20)
      {
        ball.ApplyForce(LEFT);
      }
      else if (ball.getCenter().x < 20)
      {
        ball.ApplyForce(RIGHT);
      }
      if (ball.getCenter().y < 0)
      {
        ball.ApplyForce(DOWN);
      }
      if (ball.getCenter().y > SCREEN_HEIGHT + 20)
      {
        game.Delete(ball, 1);
        ballCount -= 1;
        if(ballCount<=0) {
          move = true;
        } 
      }
    }
    vector<GO> &obstacleLayer = game.GetLayer(2);
    for (int i = 0; i < obstacleLayer.size(); i++)
    {
      GO &obstacle = obstacleLayer.at(i);
      if (obstacle.isColliding())
      {
        game.Delete(obstacle, 2);
      }
      else if (move)
      {
        obstacle.SetDest(vec2(obstacle.getCenter().x, obstacle.getCenter().y - 50));
      }
    }
    if (move)
    {
      for (int i = 0; i < rand() % 4 + 1; i++)
      {
        GO &obj = game.Spawn(GO(vec2(rand() % SCREEN_WIDTH, SCREEN_HEIGHT + 50), Shape(rand() % 5 + 3, rand() % 20 + 30, Color::HSV(rand() % 361, 50, 100))), 2);
        obj.SetDest(vec2(obj.getCenter().x, 700));
      }
      move = false;
    }
    game.Update();
  }
  return 0;
  }

  void setPointer(GameControl & game, double angle)
  {
    vector<GO> &pointerLayer = game.GetLayer(0);
    vec2 dir = vec2::Angle(angle);
    for (int i = 0; i < pointerLayer.size(); i++)
    {
      pointerLayer.at(i).SetDest(TOP_CENTER + dir * (i * 50 + 50) );
    }
  }