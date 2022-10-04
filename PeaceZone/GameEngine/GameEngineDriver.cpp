#include "GameEngine.h"

void testGameStates(GameEngine* gameEngine) 
{ 
    

    Transition* newTransition = NULL;
    do {

        std::cout << "Please enter a valid command: " << std::endl;
        std::string input;
        std::getline(std::cin, input);


        // String manipulation
        std::for_each(input.begin(), input.end(), [](char& c) {
            c = ::tolower(c);
            });
        std::regex r("\\s+");
        input = std::regex_replace(input, r, "");

        // Command Filtering
        newTransition = gameEngine->checkCommandValidity(input);

    } while (newTransition == NULL);

    std::cout << "Transition succeeded!";

    //debug
    /*
    State* newState = newTransition->currentState;
    return newState;*/

   //delete com1;
   //delete com2; 

}

int main()
{
    std::cout << "Hello World!\n";

    GameEngine* gameEngine = new GameEngine();

    


    //std::cout << *gameEngine->currentState;
    //State start = new State("start",)

    /*std::string command1 = "loadmap";
    Command* com1 = new Command(command1);
    std::vector<Command*> validCommands = { com1 };
    std::string start = "start";
    State* s1 = new State(start, validCommands);*/



    testGameStates(gameEngine);


    delete gameEngine;

}
    //std::cout << *state;
