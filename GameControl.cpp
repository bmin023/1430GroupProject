// Author: Aaron Sierra
// Assignement Title: group project
// Assignment Description: Create a game
// Due Date: To be determined
// Date Created: 11/05/21
// Date Last Modified: 11/05/21

#include "GameControl.h"

GameControl::GameControl() : g(SCREEN_HEIGHT, SCREEN_WIDTH)
{
    lastTime = getTime();
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            g.plotPixel(x, y, BLANK.R, BLANK.G, BLANK.B);
        }
    }
}

GO &GameControl::Spawn(GO gameObject, int layer)
{
    gameObjects[layer].push_back(gameObject);
    GO &go = gameObjects[layer].back();
    go.Init();
    return go;
}

void GameControl::Text(string text, vec2 pos, int size, int layer, bool back, Color color, bool del)
{
    TextObject t(text, pos, size, color, back, del);
    textObjects[layer].push_back(t);
}

void GameControl::Delete(int layer, int index)
{
    gameObjects[layer].at(index).erase(g);
    gameObjects[layer].erase(gameObjects[layer].begin() + index);
    // Reinitialize(layer);
}
void GameControl::Delete(GO &object, int layer)
{
    object.erase(g);
    // Nice little linear search
    bool found = false;
    for (int i = 0; i < gameObjects[layer].size() && !found; i++)
    {
        if (&(gameObjects[layer].at(i)) == &object)
        {
            gameObjects[layer].erase(gameObjects[layer].begin() + i);
            found = true;
        }
    }
    Reinitialize(layer);
}
void GameControl::Reinitialize(int layer)
{
    for (int i = 0; i < gameObjects[layer].size(); i++)
    {
        gameObjects[layer].at(i).Init();
    }
}
vector<GO> &GameControl::GetLayer(int layer)
{
    return gameObjects[layer];
}
unsigned int GameControl::getTime()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}
void GameControl::Update()
{
    if (g.getQuit())
    {
        Quit();
    }
    if (g.kbhit())
    {
        kbhit = true;
        if (!downed && !down)
        {
            down = true;
        }
        else
        {
            down = false;
            downed = true;
        }
        currentKey = g.getKey();
        if (currentKey == 'Q')
        {
            Quit();
        }
        else if (currentKey == 'P')
        {
            cout << "Pause!" << endl;
        }
    }
    else
    {
        kbhit = false;
        downed = false;
        currentKey = '\n';
    }
    double deltaTime = (static_cast<double>(getTime() - lastTime)) / 5;
    lastTime = getTime(); // gets the time of the last frame
    // cout << endl;
    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < gameObjects[i].size(); j++)
        {
            gameObjects[i].at(j).setDeltaTime(deltaTime);
            gameObjects[i].at(j).update(g);
        }
        for (int j = 0; j < textObjects[i].size(); j++)
        {
            if ((!textObjects[i].at(j).del || textObjects[i].at(j).color == BLANK) && textObjects[i].at(j).vis)
            {
                textObjects[i].erase(textObjects[i].begin() + j);
                j--;
            }
        }
        for (int j = 0; j < textObjects[i].size(); j++)
        {
            if (!textObjects[i].at(j).del || !textObjects[i].at(j).vis)
            {
                typer.Write(textObjects[i].at(j), g);
                textObjects[i].at(j).vis = true;
            }
            else
            {
                textObjects[i].at(j).color = BLANK;
                typer.Write(textObjects[i].at(j), g);
            }
        }
    }
    g.update();
}
void GameControl::layerCollide(int layer, int otherlayer)
{
    // checks if they are colliding
    // more informaiton on this later. CheckCollision(gameObject)
    for (int i = 0; i < gameObjects[layer].size(); i++)
    {
        for (int j = 0; j < gameObjects[otherlayer].size(); j++)
        {
            // call the check collision function that lucy the ray made.
            gameObjects[layer].at(i).CheckCollision(gameObjects[otherlayer].at(j));
        }
    }
}

bool GameControl::getQuit()
{
    return quit;
}

bool GameControl::Key(char k)
{
    return currentKey == k && kbhit;
}

bool GameControl::KeyDown(char k)
{
    return currentKey == k && down;
}

void GameControl::Quit()
{
    quit = true;
}

void GameControl::InitSound(string file)
{
    g.initSound(file);
}

void GameControl::Sound(string file)
{
    g.playSound(file);
}