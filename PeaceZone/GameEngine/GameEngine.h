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
#include "../LoggingObserver/LoggingObserver.h"


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

class GameEngine : public ILoggable, public Subject{
public:
    // Data Members
    Map* activeMap;
    State* currentState;
    std::vector<State*> gameStates;
    std::vector<Command*> gameCommands;
    CommandProcessor* cmdProcessor;
    std::vector<Player*> playerList;
    Deck* gameDeck;
    Player* neutralPlayer;

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

    std::string mainGameLoop(int turnLimit = -1);
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();
    //Method that updates the commandProcessor validCommands
    void updateCmdProcessor();

    //Method that adds players 
    void addPlayer(std::string playerName);

    // Method to choose between console input or file input
    void chooseInputMode(std::string inputString = "");

    std::string stringToLog() override;
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
    //Transition method that changes the current state of the game
    void transitionState(GameEngine* gameEngine, int stateNumber, std::string input);
};

class Tournament {
public:
    static void tournamentMode(std::string tournamentMode);
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

// Free function for game state testings
static void testCommandProcessor();



