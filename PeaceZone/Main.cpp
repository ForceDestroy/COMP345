#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

#include <iostream>

#include "GameEngine/GameEngine.h"
#include "GameEngine/GameEngineDriver.cpp"
#include "GameEngine/TournamentDriver.cpp"
#include "Cards/CardsDriver.cpp"
#include "Map/MapDriver.cpp"
#include "Player/PlayerDriver.cpp"
#include "Orders/OrdersDriver.cpp"
#include "CommandProcessing/CommandProcessingDriver.cpp" 
#include "LoggingObserver/LoggingObserverDriver.cpp"
#include "Player/PlayerStrategiesDriver.cpp"

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
    std::cout << "\nTesting Command Processor" << std::endl;
    //testCommandProcessor();

    std::cout << "\n==================================================" << std::endl;

    std::cout << "\nTesting Game Engine Startup Phase" << std::endl;
    //file C:\Users\Mimi\Documents\GitHub\COMP345\PeaceZone\CommandProcessing\CommandProcessorCommands.txt
    GameEngine* gameEngine = new GameEngine();

    testTournament(gameEngine);

    testHumanStrategies();
	
    //testComputerStrategies(gameEngine);
    
    //testStartupPhase(gameEngine);

    //testGameStates(gameEngine);

    std::cout << "\n==================================================" << std::endl;

    std::cout << "\nTesting Main Game Loop" << std::endl;

    //testMainGameLoop(gameEngine);

    std::cout << "\n==================================================" << std::endl;

    std::cout << "\nTesting Log Observer" << std::endl;

    //testLoggingObserver();

    std::cout << "\n==================================================" << std::endl;

    std::cout << "\nTesting Order" << std::endl;

    //testOrderExecution();


    delete gameEngine;
    gameEngine = NULL;
}
