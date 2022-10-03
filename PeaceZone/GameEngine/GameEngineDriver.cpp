#include "GameEngine.h"
#include "GameEngineDriver.h";

State* GameEngineDriver::testGameStates()
{
    std::string command1 = "load map";
    std::string command2 = "validate map";
    Command* com1 = new Command(command1);
    Command* com2 = new Command(command2);
    std::vector<Command*> validCommands = {com1, com2};
    std::string start="start";
    State* s1=new State(start, validCommands);
    

    return s1;

   delete com1;
   delete com2; 

}
