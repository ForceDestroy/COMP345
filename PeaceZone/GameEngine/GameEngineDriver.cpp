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
            //**let the user know the state**
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

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    std::cout << "Hello User! Welcome to PeaceZone!" << std::endl;

    GameEngine* gameEngine = new GameEngine();

    testGameStates(gameEngine);

    delete gameEngine;
}