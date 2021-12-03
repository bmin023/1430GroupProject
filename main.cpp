#include <iostream>

#include "GameControl.h"

// Lucy was here

void setPointer(GameControl &game, double angle);

int main(int argc, char **argv)
{
  int score = 0;
  int count = 0;
  bool move = false;
  double angle = PI / 2;
  srand(time(0));
  GameControl game;
  game.Spawn(GO(TOP_CENTER, Shape(10, 5, RED)), 0);
  game.Spawn(GO(TOP_CENTER, Shape(10, 10, RED)), 0);
  setPointer(game, angle);
  enum gameState
  {
    TITLE,
    PLAY,
    LOSE,
  };
  gameState state = TITLE;
  while (!game.getQuit())
  {
    // Play game
    // Title screen
    while (state == TITLE && !game.getQuit())
    {
      // display title screen
      game.Text("Ball Game!", vec2(160, 160), 5, 1, false, NOTWHITE, true);
      game.Text("Arrow keys to aim", vec2(140, 260), 3, 1, false, NOTWHITE, true);
      game.Text("Space to launch ball", vec2(120, 220), 3, 1, false, NOTWHITE, true);
      game.Text("Hit space to start", vec2(140, 500), 3, 1, false, NOTWHITE, true);
      game.Update();
      if (game.Key(' '))
      {
        state = PLAY;
      }
    }

    while (state == PLAY && !game.getQuit())
    {
      game.layerCollide(1, 2);
      game.Text("Score:" + to_string(score) + " ", vec2(15, 25), 3, 3, true);
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
      else if (game.KeyDown(' '))
      {
        Color randColor = Color::HSV(count % 361, 70, 100);
        count += 10;
        GO &ball = game.Spawn(GO(TOP_CENTER, Shape(10, 20, randColor)), 1);
        ball.setMoveMethod(MoveMethod::PHYSICS);
        ball.ApplyForce(vec2::Angle(angle) * 3);
        score -= 3;
      }
      vector<GO> &ballLayer = game.GetLayer(1);
      int ballCount = ballLayer.size();
      for (int i = 0; i < ballLayer.size(); i++)
      {
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
          if (ballCount <= 0)
          {
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
          score += 10;
        }
        else if (move)
        {
          obstacle.SetDest(vec2(obstacle.getCenter().x, obstacle.getCenter().y - 50));
        }
        else if (obstacleLayer.at(i).getCenter().y <= 0)
        {
          state = LOSE;
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
      for (int i = 0; i < obstacleLayer.size(); i++)
      {
        game.Delete(obstacleLayer.at(i), 2);
      }
      while (state == LOSE && !game.getQuit())
      {
        game.Text("Game over", vec2(160, 160), 5, 1, false, NOTWHITE, true);
        if(game.Key(' ')) {
          state = TITLE;
        }
        game.Update();
      }

      game.Update();
    }
  }

  return 0;
}

void setPointer(GameControl &game, double angle)
{
  vector<GO> &pointerLayer = game.GetLayer(0);
  vec2 dir = vec2::Angle(angle);
  for (int i = 0; i < pointerLayer.size(); i++)
  {
    pointerLayer.at(i).SetDest(TOP_CENTER + dir * (i * 50 + 50));
  }
}
