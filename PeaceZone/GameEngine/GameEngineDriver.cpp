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


inline void testStartupPhase(GameEngine* gameEngine){
    std::string input;

    do {
        std::cout << "Would you like to test command processor through console or a file? Type \"console\" or \"file <filepath>\"" << std::endl;
        std::getline(std::cin, input);

    } while (!input._Equal("console") && !(input.find("file") != std::string::npos));

    gameEngine->chooseInputMode(input);

    gameEngine->startupPhase();
       
    std::cout << "End of startup phase. "<< std::endl << std::endl;

}

inline void testMainGameLoop(GameEngine* gameEngine) {
    gameEngine->mainGameLoop();
}
