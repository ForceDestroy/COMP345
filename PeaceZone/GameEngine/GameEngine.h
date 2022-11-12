#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <map>
#include <experimental/filesystem>
#include <algorithm>
#include <random>
#include <cmath> 
#include "../CommandProcessing/CommandProcessing.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Orders/Orders.h" 


#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


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
    Map* activeMap;
    State* currentState;
    std::vector<State*> gameStates;
    std::vector<Command*> gameCommands;
    CommandProcessor* cmdProcessor;
    std::vector<Player*> playerList;
    Deck* gameDeck;

    // Constructors
    GameEngine();
    GameEngine(const GameEngine& g1);
    ~GameEngine();

    // Methods
    GameEngine& operator=(const GameEngine&);
    friend std::ostream& operator<<(std::ostream& out, const GameEngine& gameEngine);
    //Checks the validity of a command input
    bool checkCommandValidity(std::string input);
    //Method that implements a command based user interaction mechanism to start the game 
    void startupPhase();

    //Method that updates the commandProcessor validCommands
    void updateCmdProcessor();

    //Method that adds players 
    void addPlayer(std::string playerName);
};

class Transition{
public:
    // Data Members
    std::string name;
    

    // Constructors
    Transition();
    Transition(std::string name);
    Transition(const Transition &t1);
    ~Transition();

    // Methods
    Transition& operator=(const Transition &);
    friend std::ostream &operator<<(std::ostream &out, const Transition &transition);
    
private:
    //Transition method that changes the current state of the game
    void transitionState(GameEngine* gameEngine, int stateNumber, std::string input);


    
};

// Free function for game state testings
static void testGameStates(GameEngine* gameEngine);

static void testStartupPhase(GameEngine* gameEngine);

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





