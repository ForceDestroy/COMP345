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


inline void testHumanStrategies()
{
    // Testing for everything but playing cards
    std::cout << "Testing human players." << std::endl;
    Player* p1 = new Player("p1");
    p1->reinforcementPool = 100;
    std::cout << p1->reinforcementPool << std::endl;
    p1->territories->push_back(new Territory(1, "t1", 1));
    p1->territories->push_back(new Territory(2, "t2", 1));
    p1->territories->at(0)->neighbors.push_back(p1->territories->at(1));
    p1->territories->at(1)->neighbors.push_back(p1->territories->at(0));
    p1->territories->at(0)->armyCount = 100;
    p1->strategy = new HumanPlayerStrategy();
    p1->strategy->issueOrder(p1);
    std::cout << *p1->listOfOrders << std::endl;
}