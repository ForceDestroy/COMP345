#include "../GameEngine/GameEngine.h"

inline void testTournament(GameEngine* gameEngine) {

    Command* currentCommand = gameEngine->cmdProcessor->getCommand();

    //verify the syntax
    std::string errorCheck = "Error";

    //Use the effect of a Command object to verify if it is invalid 
    if (currentCommand->effect.find(errorCheck) != std::string::npos)
    {
        std::cout << currentCommand->effect << std::endl;
    }
    else {
        std::cout << "Command is valid" << std::endl;
    }

    std::string tournamentString = currentCommand->name;

    Tournament::tournamentMode(tournamentString);
}