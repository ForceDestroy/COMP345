#include <iostream>
#include "GameEngine/GameEngineDriver.h"


int main()
{
    std::cout << "Hello World!\n";

    State* s2=GameEngineDriver::testGameStates();
    
    std::cout << *s2;

    delete s2;

}
