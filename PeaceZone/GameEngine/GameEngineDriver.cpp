#include "GameEngine.h"

int testGameStates()
{
    Command* loadmap =new Command();
    std::string start="start";
    State* s1=new State(start, *loadmap);
    std::cout << s1 << std::endl;

}