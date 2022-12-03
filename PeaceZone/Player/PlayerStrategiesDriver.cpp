#include "../GameEngine/GameEngine.h"
inline void testComputerStrategies(GameEngine *gameEngine) 
{
    std::string input;

    //Ask the user which mode to read the commands from
    gameEngine->chooseInputMode();


    gameEngine->startupPhase();

    std::cout << "End of startup phase. " << std::endl << std::endl;

    gameEngine->playerList.at(0)->strategy = new CheaterPlayerStrategy();
    gameEngine->playerList.at(1)->strategy = new BenevolentPlayerStrategy();
    gameEngine->playerList.at(2)->strategy = new AggressivePlayerStrategy();

    gameEngine->mainGameLoop();

}