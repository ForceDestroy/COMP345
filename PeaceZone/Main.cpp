#include <iostream>
#include "GameEngine/GameEngineDriver.cpp"


int main()
{
    std::cout << "Hello World!\n";

    //GameEngineDriver
    State* s1 = testGameStates();

    std::cout << s1;

    delete s1;

}
