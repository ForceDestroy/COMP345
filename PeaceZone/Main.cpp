#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

#include <iostream>

#include "GameEngine/GameEngine.h"
#include "GameEngine/GameEngineDriver.cpp"

#include "Map/MapDriver.cpp"

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    // Map Tester
    testLoadMaps();
    
    // GameEngine Tester
    GameEngine* gameEngine = new GameEngine();

    testGameStates(gameEngine);

    delete gameEngine;
}
