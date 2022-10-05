#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <regex>
#include <map>

#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


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

class GameEngine {
public:
    // Data Members
    State* currentState;
    std::vector<State*> gameStates;
    std::vector<Command*> gameCommands;


    // Constructors
    GameEngine();
    GameEngine(const GameEngine& g1);
    ~GameEngine();

    // Methods
    GameEngine& operator=(const GameEngine&);
    friend std::ostream& operator<<(std::ostream& out, const GameEngine& gameEngine);
    bool checkCommandValidity(std::string input);


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
    
    void transitionState(GameEngine* gameEngine, int stateNumber, std::string input);


    
};

// Free function for game state testings
static void testGameStates(GameEngine* gameEngine);

// State enums for handling 
static enum stateNames;

// Map for enums for state handling
static std::map<std::string, stateNames> stateEnumToStringMap;

// Function to initialize the map for enums for state handling
void initializeEnumToStringMap();

// Function to call the map to convert the string to corresponding enum position
int enumToStringMapHandling(std::string input);

//Helper function used to unify strings
extern std::string stringUnifier(std::string input);





