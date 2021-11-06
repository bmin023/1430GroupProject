#ifndef GAMECONTROL_H_INCLUDED
#define GAMECONTROL_H_INCLUDED

#include "GO.h"
#include <vector>
#include "SDL_Plotter.h"
#include <chrono>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int LAYERS = 4;

//GameControl class - Aaron
// (Obviously change out my documentation for your own)
class GameControl
{
  private:
    SDL_Plotter g;
    vector<GO> gameObjects[LAYERS];
    int getTime();
    int lastTime;
  public:
    GameControl(): g(SCREEN_WIDTH,SCREEN_HEIGHT){lastTime = getTime();};
    //Add a game object to the gameObjects vector
    // Return back that game object so that we can mess with it later.
    GO& Spawn(GO gameObject, int layer);
    //Remove a game object from the gameObjects vector
    void Delete(int layer, int index);
    // Return a layer of game objects
    vector<GO>& GetLayer(int layer);
    //Where all the magic happens, update all the game objects
    // and update the screen.
    // Eventually this will also handle collisions.
    // But for now, it just updates the screen.
    void Update();

};

#endif // GAMECONTROL_H_INCLUDED 