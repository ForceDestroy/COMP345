#include "GameEngine.h"

#pragma region Command
// Default Constructor - Command
Command::Command() = default;

// Destructor - Command
Command::~Command() = default;

//Constructor - Command
Command::Command(std::string name)
{
    this->name = name;
}

//Copy constructor - Command
Command::Command(const Command &c1)
{
    this->name = c1.name;
}

// Assignment Operator - Command
Command &Command::operator=(const Command &c1)
{
    this->name = c1.name;

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Command &command)
{
    out << "[" << command.name << " ]";

    return out;
}

#pragma endregion

#pragma region State
// Default Constructor - State
State::State() = default;

// Destructor - State
State::~State() = default;

//Constructor - State
State::State(std::string name, std::vector<Command*> validCommands)
{
    this->name=name;
    for (int i = 0; i < validCommands.size(); i++)
        this->validCommands.push_back(validCommands[i]);
}

//Copy constructor - State
State::State(const State &s1)
{
    this->name=s1.name;
    this->validCommands=s1.validCommands;
}

// Assignment Operator - State
State &State::operator=(const State &s1)
{
    this->name=s1.name;
    this->validCommands=s1.validCommands;

    return *this;
}

std::ostream &operator<<(std::ostream &out, const State &state)
{
    out << "{ Name: " << state.name << ", ";
    out << "validCommands: ";
    for (int i = 0; i < state.validCommands.size(); i++)
        out << *state.validCommands[i] << " ";
    out <<  "}";
    return out;
}

#pragma endregion

#pragma region Transition



// Default Constructor - Transition
Transition::Transition() = default;

// Destructor - Transition
Transition::~Transition() = default;

//Constructor - Transition
Transition::Transition(std::string name, State* currentState)
{
    this->name = name;
    this->currentState = currentState;
}

//Copy constructor - Transition
Transition::Transition(const Transition &c1)
{
    this->name = c1.name;
    this->currentState = currentState;
}

// Assignment Operator - Transition
Transition &Transition::operator=(const Transition &t1)
{
    this->name = t1.name;
    this->currentState = currentState;

    return *this;
}

// Stream Insertion Operator - Transition
std::ostream &operator<<(std::ostream &out, const Transition &transition)
{
    out << "{ Transition name: " << transition.name << ",}";

    return out;
}

 void Transition::transitionState(GameEngine* gameEngine )
 {

    switch(gameEngine->currentState->name) {
      case 0:
        // code block 
        break;
      case 1:
        // code block
        break;
      default:
        // code block
}
 }


#pragma endregion

#pragma region GameEngine

// Default Constructor - GameEngine
GameEngine::GameEngine()
{
     //Commands creation
    Command* loadMap = new Command("loadmap");
    Command* validateMap = new Command("validatemap");
    Command* addPlayer = new Command("addplayer");
    Command* assignCountries = new Command("assigncountries");
    Command* issueOrder = new Command("issueorder");
    Command* endIssueOrders = new Command("endissueorders");
    Command* execOrder = new Command("execorder");
    Command* endExecOrders = new Command("endexecorders");
    Command* winCommand = new Command("win");
    Command* play = new Command("play");
    Command* end = new Command("end");

    //Creating the vector of game commands
    this->gameCommands.push_back(loadMap);
    this->gameCommands.push_back(validateMap);
    this->gameCommands.push_back(addPlayer);
    this->gameCommands.push_back(assignCountries);
    this->gameCommands.push_back(issueOrder);
    this->gameCommands.push_back(endIssueOrders);
    this->gameCommands.push_back(execOrder);
    this->gameCommands.push_back(endExecOrders);
    this->gameCommands.push_back(winCommand);
    this->gameCommands.push_back(play);
    this->gameCommands.push_back(end);


    //Creating valid commands vector for each state
    std::vector<Command*> startValidCommands = {loadMap};
    std::vector<Command*> mapLoadedValidCommands = {loadMap, validateMap};
    std::vector<Command*> mapValidatedValidCommands = {addPlayer};
    std::vector<Command*> playersAddedValidCommands = {addPlayer, assignCountries};
    std::vector<Command*> assignReinforcementValidCommands = {issueOrder};
    std::vector<Command*> issueOrdersValidCommands = {issueOrder, endIssueOrders};
    std::vector<Command*> executeOrdersValidCommands = {execOrder, endExecOrders,winCommand};
    std::vector<Command*> winValidCommands = {play, end};

    //Creating the states
    State* start=new State("Start", startValidCommands);
    State* mapLoaded=new State("Map loaded", mapLoadedValidCommands);
    State* mapValidated=new State("Map validated", mapValidatedValidCommands);
    State* playersAdded=new State("Players added", playersAddedValidCommands);
    State* assignReinforcement=new State("Assign reinforcement", assignReinforcementValidCommands);
    State* issueOrders=new State("Issue orders", issueOrdersValidCommands);
    State* executeOrders=new State("Execute orders", executeOrdersValidCommands);
    State* win=new State("Win", winValidCommands);

    //creating a vector of states
    std::vector<State*> gameStates={start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win };

    for (int i = 0; i < gameStates.size(); i++)
        this->gameStates.push_back(gameStates[i]);

    //Setting the current state to Start
    this->currentState=start;


};

// Destructor - GameEngine
GameEngine::~GameEngine()
{
    //Deleting the State and Command objects
    for (Command* c : gameCommands) {
        delete c;
    }

    for (State* s : gameStates) {
        delete s;
    }
        


};


// Copy constructor - GameEngine
GameEngine::GameEngine(const GameEngine &g1)
{
    this->currentState = g1.currentState;
}

// Assignment Operator - GameEngine
GameEngine &GameEngine::operator=(const GameEngine &c1)
{
    this->currentState = c1.currentState;

    return *this;
}

// Stream Insertion Operator - GameEngine
std::ostream &operator<<(std::ostream &out, const GameEngine &gameEngine)
{
    out << "[Current state of the game:" << gameEngine.currentState << " ]";

    return out;
}



 // Command Validity Checking
Transition* GameEngine::checkCommandValidity(std::string input) {


    // vector comparing
    int count = 0;
    for (int i = 0; i < this->currentState->validCommands.size(); i++)
    {
        if (this->currentState->validCommands[i]->name._Equal(input)) {
            count++;
        }
    }
    if (count != 1) {
        std::cout << "The entered command is invalid for the current state: " << this->currentState->name << "\n";
        return NULL;
    }

    // call transition to change gamestate
   std::cout << "The entered command is valid!";


    
}

 

#pragma endregion


#pragma region Helpers

static enum stateNames { start, maploaded, mapvalidated, playersadded, assignreinforcement, issueorders, executeorders, win };

static std::string stringUnifier(std::string input) {
    
    std::for_each(input.begin(), input.end(), [](char& c) {
        c = ::tolower(c);
        });
    std::regex r("\\s+");
    input = std::regex_replace(input, r, "");

}

#pragma endregion