#include <iostream>
#include "GameEngine/GameEngineDriver.h"


int main()
{
    std::cout << "Hello World!\n";
    //State start = new State("start",)

    std::string command1 = "load map";
    Command* com1 = new Command(command1);
    std::vector<Command*> validCommands = { com1 };
    std::string start = "start";
    State* s1 = new State(start, validCommands);

    

    State* s2=GameEngineDriver::testGameStates(start, s1);
    
    std::cout << *s2;

    delete s1;
    delete s2;

}
