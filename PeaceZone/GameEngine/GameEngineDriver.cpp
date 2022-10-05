#include "GameEngine.h"

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

        if (gameEngine->currentState->name._Equal("endState")) {
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
    std::cout << "Hello World!\n";

    //map<string, pair<string, string> > myMap;
    


    GameEngine* gameEngine = new GameEngine();


    


    /*std::cout << "Current state of the game: " << *gameEngine->currentState << "\n";*/

    



    testGameStates(gameEngine);


    delete gameEngine;
}