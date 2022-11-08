#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

#include <iostream>

#include "GameEngine/GameEngine.h"
#include "GameEngine/GameEngineDriver.cpp"
#include "Cards/CardsDriver.cpp"
#include "Map/MapDriver.cpp"
#include "Player/PlayerDriver.cpp"
#include "Orders/OrdersDriver.cpp"
#include "CommandProcessing/CommandProcessingDriver.cpp" 

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    std::cout << "COMP345 - PeaceZone" << std::endl;

    //Map Tester
    std::cout << "\nTesting Map Loader" << std::endl;
    //testLoadMaps();
    std::cout << "\n==================================================" << std::endl;

    //Orders Tester
    std::cout << "\nTesting Orders" << std::endl;
    //testOrdersList();
    std::cout << "\n==================================================" << std::endl;
    
    //Card Tester
    std::cout << "\nTesting Cards" << std::endl;
    //testCards();
    std::cout << "\n==================================================" << std::endl;

    //Player Tester
    std::cout << "\nTesting Player" << std::endl;
    //testPlayer();
    std::cout << "\n==================================================" << std::endl;

    //GameEngine Tester
    std::cout << "\nTesting Game Engine" << std::endl;
    GameEngine* gameEngine = new GameEngine();
    testCommandProcessor(gameEngine);
    //testGameStates(gameEngine);

    delete gameEngine;
    std::cout << "\n==================================================" << std::endl;
}
