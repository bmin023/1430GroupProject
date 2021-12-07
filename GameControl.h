/* Author: Brendon Kofink
 *         Johann Rajadurai
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Ball Game
 * Assignment Description: user can launch balls to hit objects.
 * Due Date: 12/08/2021
 * Date Created: 11/05/2021
 * Date Last Modified: 12/04/2021
 */

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

class GameControl
{
  private:
    SDL_Plotter g;
    vector<GO> gameObjects[LAYERS];
    vector<TextObject> textObjects[LAYERS];
    unsigned int lastTime;
    char currentKey;
    bool quit = false;
    bool down,downed = false;
    bool kbhit = false;
    Typer typer;
    double deltaTime;
    /*
    * description: Gets the current time in milliseconds
    * return: unsigned int
    * precondition: none
    * postcondition: The current time in milliseconds is returned
    */
    unsigned int getTime();
    /*
    * description: Reinitializes each game object in a layer
    * return: void
    * precondition: That I didn't think far enough ahead to see this problem
    * postcondition: Each game object in a layer is reinitialized
    */
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
    /*
    * description: Creates a text object
    * return: void
    * precondition: there is a text object and a layer
    * postcondition: the text object is now made at the layer requested
    */
    void Text(string text, vec2 pos, int size, int layer, bool back = false, Color color = NOTWHITE, bool del = false);
    //Remove a game object from the gameObjects vector
    /*
    * description: deletes a game object from game objects vector
    * return: void
    * precondition: there is an object to kill
    * postcondition: the object is now not alive
    */
    void Delete(int layer, int index);
    /*
    * description: deletes a text object from game objects vector
    * return: void
    * precondition: there is an object to kill
    * postcondition: the object is now not alive
    */
    void Delete(GO &, int);
    // Return a layer of game objects
    /*
    * description: grabs a layer of game objects
    * return: GO
    * precondition: there is a layer at the int called
    * postcondition: the layer at int is returned
    */
    vector<GO>& GetLayer(int layer);

    /*
    * description: Gets the delta time
    * return: double
    * precondition: there is a delta time
    * postcondition: the delta time is returned
    */
    double DeltaTime();

    //Where all the magic happens, update all the game objects
    // and update the screen.
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

    /*
    * description: Gets the quit bool
    * return: bool
    * precondition: there is a quit bool
    * postcondition: the quit bool is returned
    */
    bool getQuit();
    /*
    * description: Returns if a key is pressed
    * return: bool
    * precondition: none
    * postcondition: whether or not a key is pressed is returned
    */
    bool Key(char);
    /*
    * description: Returns if this is the first frame a key is pressed
    * return: bool
    * precondition: none
    * postcondition: whether or not a key is pressed is returned
    */
    bool KeyDown(char);
    /*
    * description: Quits the game
    * return: void
    * precondition: none
    * postcondition: the game is now quit
    */
    void Quit();

    /*
    * description: Inits a sound
    * return: void
    * precondition: the given sound file exists
    * postcondition: the sound is now inited
    */
    void InitSound(string);

    /*
    * description: Plays a sound
    * return: void
    * precondition: the given sound file exists and is inited
    * postcondition: the sound is now played
    */
    void Sound(string);
};

const vec2 TOP_CENTER = RIGHT * (SCREEN_WIDTH / 2);

#endif // GAMECONTROL_H_INCLUDED 
