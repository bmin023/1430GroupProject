#ifndef GAMECONTROL_H_INCLUDED
#define GAMECONTROL_H_INCLUDED

#include "GO.h"
#include <vector>
#include "SDL_Plotter.h"
#include <chrono>
#include "Typer.h"
#include <string>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;
const int LAYERS = 4;

using namespace std;

//GameControl class - Aaron
// (Obviously change out my documentation for your own)
class GameControl
{
  private:
    SDL_Plotter g;
    vector<GO> gameObjects[LAYERS];
    vector<TextObject> textObjects[LAYERS];
    unsigned int getTime();
    unsigned int lastTime;
    char currentKey;
    bool quit = false;
    bool down,downed = false;
    bool kbhit = false;
    Typer typer;
    double deltaTime;
    void Reinitialize(int layer);
  public:
    /*
    * description: Creates the screen and it initializest the game control
    * return: default constructor
    * precondition: a gamecontrol is made w/out parameters
    * postcondition: the screen is now made
    */
    GameControl();
    //Add a game object to the gameObjects vector
    // Return back that game object so that we can mess with it later.
    /*
    * description: spawns a game object
    * return: GO
    * precondition: there is a game object and a layer
    * postcondition: the game object is now made at the layer requested
    */
    GO& Spawn(GO gameObject, int layer);
    void Text(string text, vec2 pos, int size, int layer, bool back = false, Color color = NOTWHITE, bool del = false);
    //Remove a game object from the gameObjects vector
    /*
    * description: deletes a game object from game objects vector
    * return: void
    * precondition: there is an object to kill
    * postcondition: the object is now not alive
    */
    void Delete(int layer, int index);
    void Delete(GO &, int);
    // Return a layer of game objects
    /*
    * description: grabs a layer of game objects
    * return: GO
    * precondition: there is a layer at the int called
    * postcondition: the layer at int is returned
    */
    vector<GO>& GetLayer(int layer);

    double DeltaTime();
    //Where all the magic happens, update all the game objects
    // and update the screen.
    // Eventually this will also handle collisions.
    // But for now, it just updates the screen.
    /*
    * description: updates the screen and handles the collisions
    * return: void
    * precondition: the function is called
    * postcondition: the objects are updated
    */
    void Update();
    /*
    * description: runs the collison function on all objects in 2 desired layers
    * return: void
    * precondition: there is are two layers
    * postcondition: the layers have been run through the collision function
    */
    void layerCollide(int layer, int otherlayer);

    bool getQuit();
    bool Key(char);
    bool KeyDown(char);
    void Quit();

    void InitSound(string);
    void Sound(string);
};

const vec2 TOP_CENTER = RIGHT * (SCREEN_WIDTH / 2);

#endif // GAMECONTROL_H_INCLUDED 