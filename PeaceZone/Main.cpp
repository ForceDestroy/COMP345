#include <iostream>
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameEngineDriver.cpp"




int main()
{
    


    //GameEngine Tester
    GameEngine* gameEngine = new GameEngine();

    testGameStates(gameEngine);

    delete gameEngine;
}