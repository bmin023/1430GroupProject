/* Author: Brendon Kofink
 *         Johann Rajadurai
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Ball Game
 * Assignment Description: user can launch balls to hit objects.
 * Due Date: 12/08/2021
 * Date Created: 10/19/2021
 * Date Last Modified: 12/08/2021
 */

#include <iostream>

#include "GameControl.h"

/*
 * description: Sets the dots to point through an angle.
 * return: void
 * precondition: The angle is in radians.
 * postcondition: The dots' destination are set to point through the angle.
 */
void setPointer(GameControl &game, double angle);
/*
 * description: Creates rainbow text that changes based on time.
 * return: void
 * precondition: game is a valid GameControl object.
 * postcondition: The rainbow text is created.
 */
void RainbowText(GameControl &game, string text, vec2 pos, int size, int time);

int main(int argc, char **argv)
{
  // Scores and counters
  int score = 0;
  int prevScore = 0;
  int count = 0;
  double gameTime = 0;

  // Move is true the frame the ball falls off screen
  bool move = false;

  // Angle of the pointer
  double angle = 3 * PI / 2;

  // For the '-10' text
  double lastShot = 0;
  string scoreMod = "";

  enum gameState
  {
    TITLE,
    PLAY,
    LOSE,
  };
  gameState state = TITLE;

  // Initialize the game
  GameControl game;
  game.InitSound("Drop.wav");

  // Initialize the pointer
  game.Spawn(GO(TOP_CENTER, Shape(10, 5, RED)), 3);
  game.Spawn(GO(TOP_CENTER, Shape(10, 10, RED)), 3);
  setPointer(game, angle);

  srand(time(0));

  // Game Loop
  while (!game.getQuit())
  {

    // Title Screen
    while (state == TITLE && !game.getQuit())
    {
      // display title screen
      RainbowText(game, "Ball Game!", vec2(80, 160), 8, gameTime);
      game.Text("Arrow keys to aim", vec2(140, 260), 3, 1, false, NOTWHITE, true);
      game.Text("Space to launch ball", vec2(120, 220), 3, 1, false, NOTWHITE, true);
      game.Text("Hit space to start", vec2(140, 500), 3, 1, false, NOTWHITE, true);
      if (game.KeyDown(' '))
      {
        state = PLAY;  //if space is hit, game is in PLAY state
      }
      move = true;
      game.Update();
      gameTime += game.DeltaTime();
    }

    angle = PI / 2;
    setPointer(game, angle);

    // Main Game
    while (state == PLAY && !game.getQuit())
    {
      // Check for collisions
      game.layerCollide(1, 2);

      // Check for input.
      // Left and Right arrow move the pointer.
      if (game.Key(LEFT_ARROW))
      {
        angle += 0.01;
        setPointer(game, angle);
        // Clamp the angle
        if (angle > PI)
        {
          angle = PI;
        }
      }
      else if (game.Key(RIGHT_ARROW))
      {
        angle -= 0.01;
        setPointer(game, angle);
        // Clamp the angle
        if (angle < 0)
        {
          angle = 0;
        }
      }
      // Space launches the ball.
      else if (game.KeyDown(' '))
      {
        // Count tracks the number of balls launched.
        // col takes that number and uses it to spin around the color wheel.
        Color col = Color::HSV((count * 20) % 361, 70, 100);
        count += 1;

        // Create the ball. Make it physics based and set its velocity.
        GO &ball = game.Spawn(GO(TOP_CENTER, Shape(10, 15, col)), 1);
        ball.setMoveMethod(MoveMethod::PHYSICS);
        ball.ApplyForce(vec2::Angle(angle) * 3);

        // You lose points for each ball you launch.
        // Scaled by your score.
        score -= score / 15 + 1;
        scoreMod = to_string(-(score / 15 + 1));
        lastShot = gameTime;
      }

      // Clamp Score
      if (score < 0)
      {
        score = 0;
      }

      // Go through each ball
      vector<GO> &ballLayer = game.GetLayer(1);
      int ballCount = ballLayer.size();
      for (int i = 0; i < ballLayer.size(); i++)
      {
        GO &ball = ballLayer.at(i);

        // If the ball is off screen, apply a force to away from the wall.
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
        // If it is below the screen, remove it.
        if (ball.getCenter().y > SCREEN_HEIGHT + 20)
        {
          game.Delete(ball, 1);
          ballCount -= 1;
          // If there are no more balls left on the screen,
          //  flag the obstacles to move.
          if (ballCount <= 0)
          {
            move = true;
          }
        }
      }

      // Go through each obstacle
      vector<GO> &obstacleLayer = game.GetLayer(2);
      for (int i = 0; i < obstacleLayer.size(); i++)
      {
        GO &obstacle = obstacleLayer.at(i);

        // If it collided, delete it. Play a sound too.
        if (obstacle.isColliding())
        {
          GO &deleted = game.Spawn(obstacle, 0);
          deleted.setPhysics(NOCOLLIDE);

          game.Delete(obstacle, 2);

          scoreMod = "+10";
          lastShot = gameTime;

          game.Sound("Drop.wav");
          score += 10;
        }
        else if (move)
        {
          // If flagged to move, set its destination higher. Scaled by score.
          obstacle.SetDest(vec2(obstacle.getCenter().x, obstacle.getCenter().y - 100 - score / 3));
        }
        else if (obstacleLayer.at(i).getCenter().y <= 0)
        {
          // If it got above the screen, you lose.
          state = LOSE;
        }
        // Pentagons and Triangles rotate.
        else if (obstacle.getShape().getSides() == 5)
        {
          obstacle.Rotate(.002);
        }
        else if (obstacle.getShape().getSides() == 3)
        {
          obstacle.Rotate(-.002);
        }
      }
      // If move, spawn a new row of obstacles.
      if (move)
      {
        for (int i = 0; i < rand() % 7 + 1; i++)
        {
          // Random position, size, sides, and color.
          GO &obj = game.Spawn(
              GO(vec2(rand() % SCREEN_WIDTH, SCREEN_HEIGHT + 50),
                 Shape(rand() % 6 + 3, rand() % 25 + 20,
                       Color::HSV(rand() % 361, 50, 100))),
              2);
          obj.SetDest(vec2(obj.getCenter().x, 700 - rand() % 50));
          obj.Rotate(rand() % 100 / 50.0 * PI);
        }
        move = false;
      }
      vector<GO> &delLayer = game.GetLayer(0);
      for (int i = 0; i < delLayer.size(); i++)
      {
        GO &del = delLayer.at(i);
        if (del.getShape().getColor() == BLANK)
        {
          game.Delete(del, 0);
        }
        del.Scale(1.5);
        del.SetColor(Color::Lerp(del.getShape().getColor(), BLANK, 0.05 * game.DeltaTime()));
      }

      // Display score
      game.Text("Score:" + to_string(score) + " ", vec2(15, 25), 3, 0, true);
      game.Text(scoreMod, vec2(120, 50), 3, 0, true, Color::Lerp(NOTWHITE, BLANK, (gameTime - lastShot) / 180));

      game.Update();
      gameTime += game.DeltaTime();
    }

    // In between main game and lose screen

    // Cover up the scoreMod text with spaces
    game.Text("      ", vec2(120, 50), 3, 3, true, BLANK);
    // Set the Score text to delete.
    // (Literally does the same thing as the above but different ways of doing it)
    game.Text("Score:" + to_string(score), vec2(15, 25), 3, 3, true, NOTWHITE, true);

    setPointer(game, 3 * PI / 2);

    // Go through each obstacle, set them to physics based and apply random force
    vector<GO> &obstacleLayer = game.GetLayer(2);
    for (int i = 0; i < obstacleLayer.size(); i++)
    {
      obstacleLayer.at(i).setMoveMethod(MoveMethod::PHYSICS);
      obstacleLayer.at(i).ApplyForce(UP * .75 + RIGHT * (rand() % 100 / 250.0 - .2));
    }

    // Delete all deleted objects
    int size = game.GetLayer(0).size();
    for (int i = 0; i < size; i++)
    {
      game.Delete(0, 0);
    }

    // Create an invisible object that moves from top left to center.
    GO &mover = game.Spawn(GO(vec2(15, 25), Shape(10, 10, RED)), 1);
    mover.setVisible(false);
    if (score > prevScore)
    {
      mover.SetDest(vec2(100, 200));
    }
    else
    {
      mover.SetDest(vec2(160, 200));
    }
    // Lose Screen
    while (state == LOSE && !game.getQuit())
    {
      // Make score text follow the invisible object
      game.Text("Score:" + to_string(score), mover.getCenter(), 3, 3, false, NOTWHITE, true);

      // Highscore or Game Over Title
      if (score > prevScore)
      {
        RainbowText(game, "New highscore!", vec2(100, 160), 5, gameTime);
      }
      else
      {
        game.Text("Game over", vec2(160, 160), 5, 1, false, NOTWHITE, true);
      }

      game.Text("Hit space to restart", vec2(110, 500), 3, 1, false, NOTWHITE, true);

      // Check for restart
      if (game.KeyDown(' '))
      {
        state = TITLE;
        game.Delete(mover, 1);
        if (score > prevScore)
        {
          prevScore = score;
        }
        score = 0;
      }
      game.Update();
      gameTime += game.DeltaTime();
    }
    // Delete all obstacles
    size = game.GetLayer(2).size();
    for (int i = 0; i < size; i++)
    {
      game.Delete(2, 0);
    }
  }

  return 0;
}

void setPointer(GameControl &game, double angle)
{
  vector<GO> &pointerLayer = game.GetLayer(3);
  vec2 dir = vec2::Angle(angle);
  for (int i = 0; i < pointerLayer.size(); i++)
  {
    pointerLayer.at(i).SetDest(TOP_CENTER + dir * (i * 50 + 50));
  }
}

void RainbowText(GameControl &game, string text, vec2 pos, int size, int time)
{
  int length = text.length();
  for (int i = 0; i < length; i++)
  {
    game.Text(text.substr(i, 1), pos + RIGHT * i * size * 6, size, 3, false, Color::HSV((time + i * 5) % 360, 100, 100), true);
  }
}
