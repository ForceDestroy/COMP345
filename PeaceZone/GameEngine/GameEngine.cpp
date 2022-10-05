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

 void transitionState(GameEngine* gameEngine, int stateNumber, std::string input )
 {

    switch(stateNumber) {
      case 0:
          // Start state 
          if (input._Equal("loadmap"))
          {
              //TRANSITION TO MAP LOADED STATE
			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
          } 
          break;

      case 1:
          // Map loaded state
          if (input._Equal("loadmap"))
          {
              //NO TRANSITION - SAME STATE
          }
          if (input._Equal("validatemap"))
          {
              //TRANSITION TO MAP VALIDATED STATE
              gameEngine->currentState = gameEngine->gameStates[++stateNumber];
          }
          break;

	  case 2:
          // Map validated state
          if (input._Equal("addplayer"))
          {
              //TRANSITION TO PLAYERS ADDED STATE
			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
          }

		  break;

	  case 3:
		  // Players added state

          if(input._Equal("addplayer"))
          {
			  //NO TRANSITION - SAME STATE
          }
          if (input._Equal("assigncountries"))
          {     
              //TRANSITION TO ASSIGN REINFORCEMENT STATE
			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
          }
          break;

      case 4:
          // Assign reinforcement state
          if (input._Equal("issueorder"))
          {
              //TRANSITION TO ISSUE ORDERS STATE

			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
          }
          break;

      case 5:
          // Issue Orders state
          if (input._Equal("issueorder"))
          {
              //NO TRANSITION - SAME STATE
          }
          if (input._Equal("endissueorders"))
          {
              //TRANSITION TO EXECUTE ORDERS STATE
			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
          }
          break;

      case 6:
		  // Execute Orders state
		  if (input._Equal("execorders"))
		  {
			  //NO TRANSITION - SAME STATE
		  }

          if (input._Equal("endexecorders")) {
              //TRANSITION TO ASSIGN REINFORCEMENT STATE
              gameEngine->currentState = gameEngine->gameStates[4];
          }

          if (input._Equal("win")) {
              //TRANSITION TO WIN STATE
              gameEngine->currentState = gameEngine->gameStates[++stateNumber];
          }

        
		  break;

	  case 7:
	      // Win state
		  if (input._Equal("end"))
		  {
			  //TRANSITION TO END STATE
              std::cout << "Congratulations! You won!";
              gameEngine->currentState = gameEngine->gameStates[++stateNumber];
		  }
          if (input._Equal("play")) {
              //TRANSITION TO START STATE
              gameEngine->currentState = gameEngine->gameStates[0];
          }
          break;
      default:
          std::cout << "Oh no! T.T Something went terribly wrong!";
          break;
        
        
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
    std::vector<Command*> endValidCommands = {};

    //Creating the states
    State* start=new State("Start", startValidCommands);
    State* mapLoaded=new State("Map loaded", mapLoadedValidCommands);
    State* mapValidated=new State("Map validated", mapValidatedValidCommands);
    State* playersAdded=new State("Players added", playersAddedValidCommands);
    State* assignReinforcement=new State("Assign reinforcement", assignReinforcementValidCommands);
    State* issueOrders=new State("Issue orders", issueOrdersValidCommands);
    State* executeOrders=new State("Execute orders", executeOrdersValidCommands);
    State* win=new State("Win", winValidCommands);
    State* endState = new State("end", endValidCommands);


    //creating a vector of states
    std::vector<State*> gameStates={start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win, endState };

    for (int i = 0; i < gameStates.size(); i++)
        this->gameStates.push_back(gameStates[i]);

    //Setting the current state to Start
    this->currentState=start;

    //Initializing the stateEnumToStringMap
    initializeEnumToStringMap();


}

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
        

}


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
bool GameEngine::checkCommandValidity(std::string input) {

    // vector comparing
    int count = 0;
    int stateNumber=-1;
    for (int i = 0; i < this->currentState->validCommands.size(); i++)
    {
        if (this->currentState->validCommands[i]->name._Equal(input)) {
            count++;
        }
    }
    if (count != 1) {
        std::cout << "The entered command is invalid for the current state: " << this->currentState->name << "\n";
        return false;
    }
   std::cout << "The entered command is valid!\n";
   
   // Callind the map to get the number of the state
   stateNumber=enumToStringMapHandling(stringUnifier(this->currentState->name));

   // Checking if the state number is found in map
   if (stateNumber == -1)
       return false;

   // call transition to change gamestate
   transitionState(this, stateNumber, input);
   return true;
}

 

#pragma endregion


#pragma region Helpers

static const enum stateNames { start, maploaded, mapvalidated, playersadded, assignreinforcement, issueorders, executeorders, win, endState=8};


//Helper function used to unify strings
extern std::string stringUnifier(std::string input) 
{

    std::for_each(input.begin(), input.end(), [](char& c) {
        c = ::tolower(c);
        });
    std::regex r("\\s+");
    input = std::regex_replace(input, r, "");
    return input;

}

void initializeEnumToStringMap()
{
    // Map to associate the strings with the enum values
	stateEnumToStringMap["start"] = start;
    stateEnumToStringMap["maploaded"] = maploaded;
    stateEnumToStringMap["mapvalidated"] = mapvalidated;
    stateEnumToStringMap["playersadded"] = playersadded;
    stateEnumToStringMap["assignreinforcement"] = assignreinforcement;
	stateEnumToStringMap["issueorders"] = issueorders;
    stateEnumToStringMap["executeorders"] = executeorders;
    stateEnumToStringMap["win"] = win;
    stateEnumToStringMap["endState"] = endState;


  /*  std::cout << "stateEnumToStringMap contains: "
        << stateEnumToStringMap.size()
        << " entries. " << std::endl;*/


}

 int enumToStringMapHandling(std::string input)
{
     return (stateEnumToStringMap[input]);
}

#pragma endregion