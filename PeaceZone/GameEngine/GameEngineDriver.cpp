#include "GameEngine.h"
#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

void testGameStates(GameEngine* gameEngine) 
{ 
    std::string continueInput;
    do{
		bool transitionSuccess = false;
        //A loop asking the user to enter a command as long as the command is not valid
		do {
            //Ask the user command
			std::cout << "Please enter a valid command for the current state : " << std::endl;
			std::string input;
			std::getline(std::cin, input);


			// String manipulation
			std::string cleanInput = stringUnifier(input);

			// Command Filtering
			transitionSuccess = gameEngine->checkCommandValidity(cleanInput);

		} while (!transitionSuccess);
		std::cout << "Transition succeeded! You've transitioned to the state " << gameEngine->currentState->name << ".\n";
        // If the user reached the end of the game
        if (gameEngine->currentState->name._Equal("End")) {
            std::cout << "You have reached the end of the game, thank you for testing! Goodbye! ";
            break;

        }
        //A loop asking the user to answer "yes" to continue to test and "no" to stop the testing
        do{
			std::cout << "Would you like to continue testing the game states? You are currently at state "
				<< gameEngine->currentState->name
				<< ". Write \"yes\" to continue or \"no\" to exit:" << std::endl;
			std::getline(std::cin, continueInput);
            continueInput = stringUnifier(continueInput);
        } while (!continueInput._Equal("yes") && !continueInput._Equal("no"));

        if (continueInput._Equal("no")){
            std::cout << "Thank you for testing our game states :) Goodbye!";
			break;

        }
            

    } while (!gameEngine->currentState->name._Equal("endState"));

}


void testStartupPhase(GameEngine* gameEngine){
    std::cout << "Would you like to test command processor through command input or a file? Type \"input\" or \"file\"" << std::endl;

    std::string input;


    do {
        std::getline(std::cin, input);

    } while (!input._Equal("input") && !input._Equal("file"));


    if (input._Equal("input")) {

        gameEngine->startupPhase();
       
        std::cout << "End of startup phase, command processor:  " << std::endl << gameEngine->cmdProcessor << std::endl << std::endl;
    }

    if (input._Equal("file")) {

        std::string path("C:/ProjectSchool/COMP 345/COMP345/PeaceZone/GameEngine/GameStartupCommands.txt");

        FileLineReader* flr = new FileLineReader(path);
        FileCommandProcessorAdapter* fcpa = new FileCommandProcessorAdapter(gameEngine->cmdProcessor->commandList, gameEngine->cmdProcessor->validCommands, flr);

        gameEngine->cmdProcessor = fcpa;

        gameEngine->startupPhase();
        
        std::cout << "End of startup phase, file command processor adapter:  " << std::endl << *gameEngine->cmdProcessor << std::endl << std::endl;
    }
}
