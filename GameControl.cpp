// Author: Aaron Sierra
// Assignement Title: group project
// Assignment Description: Create a game
// Due Date: To be determined
// Date Created: 11/05/21
// Date Last Modified: 11/05/21

#include "GameControl.h"


GO& GameControl::Spawn(GO gameObject, int layer){
    gameObjects[layer].push_back(gameObject);
    return gameObjects[layer].back();
}
void GameControl::Delete(int layer, int index){
    gameObjects[layer].erase(gameObjects->begin()+index);
}
vector<GO>& GameControl::GetLayer(int layer){
    return gameObjects[layer];
}
int GameControl::getTime(){
    return chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();
}
void GameControl::Update(){
    double deltaTime = (static_cast<double>(getTime() - lastTime)) /100000;
    for (int i = 0; i < LAYERS; i++){
        for (int j = 0; j < gameObjects[i].size(); j++){
            gameObjects[i].at(j).setDeltaTime(deltaTime);
            gameObjects[i].at(j).update(g);
        }
    }
    g.update();
    lastTime = getTime(); //gets the time of the last frame

}
void GameControl::layerCollide(int layer, int otherlayer){
    //checks if they are colliding
    //more informaiton on this later. CheckCollision(gameObject)
    for (int i = 0; i < gameObjects[layer].size(); i++){
        for (int j = 0; j < gameObjects[otherlayer].size(); j++){
            //call the check collision function that lucy the ray made.
            gameObjects[layer].at(i).CheckCollision(&gameObjects[otherlayer].at(j));
        }
    }

}