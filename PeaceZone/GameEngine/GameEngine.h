#pragma once
#include <iostream>
#include <iterator>
#include <list>


class State{
public:
    // Data Members
    std::string name;
    Command validCommands;

    // Constructors
    State();
    State(std::string name,Command validCommands);
    State(const State &s1);
    ~State();
};

class Transition{
public:
    // Data Members
    std::string name;
    State currentState;

    // Constructors


};

class Command{
public:
    // Data Members
    std::string name;

    // Constructors

};