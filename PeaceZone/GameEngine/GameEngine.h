#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <regex>


class Command {
public:
    // Data Members
    std::string name;

    // Constructors
    Command();
    Command(std::string name);
    Command(const Command &c1);
    ~Command();

    // Methods
    Command &operator=(const Command &);
    friend std::ostream &operator<<(std::ostream &out, const Command &Command);

};

class State{
public:
    // Data Members
    std::string name;
    std::vector<Command*> validCommands;

    // Constructors
    State();
    State(std::string name, std::vector<Command*> validCommands);
    State(const State &s1);
    ~State();

    // Methods
    State &operator=(const State &);
    friend std::ostream &operator<<(std::ostream &out, const State &State);
};

class Transition{
public:
    // Data Members
    std::string name;
    State* currentState;
    

    // Constructors
    Transition();
    Transition(std::string name, State* currentState);
    Transition(const Transition &t1);
    ~Transition();

    // Methods
    Transition& operator=(const Transition &);
    friend std::ostream &operator<<(std::ostream &out, const Transition &transition);
    
private:
    // Transition methods for testGameStates
    //Transition to go to the next state
    void transitionState(GameEngine* gameEngine);


    
};

class GameEngine{
public:
    // Data Members
    State* currentState;
    std::vector<State*> gameStates;
    std::vector<Command*> gameCommands;


    // Constructors
    GameEngine();
    GameEngine(const GameEngine &g1);
    ~GameEngine();

    // Methods
    GameEngine &operator=(const GameEngine &);
    friend std::ostream &operator<<(std::ostream &out, const GameEngine &gameEngine);
    Transition* checkCommandValidity(std::string input);

   
};

static void testGameStates(GameEngine* gameEngine);

static std::string stringUnifier(std::string input);

stateNames stateEnumConverter(std::string input);

static enum stateNames;

