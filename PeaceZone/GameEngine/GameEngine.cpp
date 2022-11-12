#include "GameEngine.h"


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

// Stream Insertion Operator - State
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
Transition::Transition(std::string name)
{
    this->name = name;
}

//Copy constructor - Transition
Transition::Transition(const Transition &c1)
{
    this->name = c1.name;
}

// Assignment Operator - Transition
Transition &Transition::operator=(const Transition &t1)
{
    this->name = t1.name;

    return *this;
}

// Stream Insertion Operator - Transition
std::ostream &operator<<(std::ostream &out, const Transition &transition)
{
    out << "{ Transition name: " << transition.name << ",}";

    return out;
}
//Transition method that changes the current state of the game using the command and the current state
void transitionState(GameEngine* gameEngine, int stateNumber, std::string input )
 {

    switch(stateNumber) {
      case 0:
          // Start state 
          if (input._Equal("loadmap"))
          {
              //TRANSITION TO MAP LOADED STATE
			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
              gameEngine->updateCmdProcessor();

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
              gameEngine->updateCmdProcessor();

          }
          break;

	  case 2:
          // Map validated state
          if (input._Equal("addplayer"))
          {
              //TRANSITION TO PLAYERS ADDED STATE
			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
              gameEngine->updateCmdProcessor();

          }

		  break;

	  case 3:
		  // Players added state

          if(input._Equal("addplayer"))
          {
			  //NO TRANSITION - SAME STATE
          }
          if (input._Equal("gamestart"))
          {     
              //TRANSITION TO GAME START STATE
			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
              gameEngine->updateCmdProcessor();

          }
          break;

      case 4:
          // Assign reinforcement state
          if (input._Equal("issueorder"))
          {
              //TRANSITION TO ISSUE ORDERS STATE

			  gameEngine->currentState = gameEngine->gameStates[++stateNumber];
              gameEngine->updateCmdProcessor();

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
              gameEngine->updateCmdProcessor();

          }
          break;

      case 6:
		  // Execute Orders state
		  if (input._Equal("execorder"))
		  {
			  //NO TRANSITION - SAME STATE
		  }

          if (input._Equal("endexecorders")) {
              //TRANSITION TO ASSIGN REINFORCEMENT STATE
              gameEngine->currentState = gameEngine->gameStates[4];
              gameEngine->updateCmdProcessor();

          }

          if (input._Equal("win")) {
              //TRANSITION TO WIN STATE
              gameEngine->currentState = gameEngine->gameStates[++stateNumber];
              gameEngine->updateCmdProcessor();

          }

        
		  break;

	  case 7:
	      // Win state
		  if (input._Equal("end"))
		  {
			  //TRANSITION TO END STATE
              std::cout << "Congratulations! You won! ";
              gameEngine->currentState = gameEngine->gameStates[++stateNumber];
              gameEngine->updateCmdProcessor();

		  }
          if (input._Equal("play")) {
              //TRANSITION TO START STATE
              gameEngine->currentState = gameEngine->gameStates[0];
              gameEngine->updateCmdProcessor();

          }
          break;
      default:
          std::cout << "Oh no! T.T Something went terribly wrong!" << std::endl;
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
    Command* gameStart = new Command("gamestart");
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
    this->gameCommands.push_back(gameStart);
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
    std::vector<Command*> playersAddedValidCommands = {addPlayer, gameStart};
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
    State* endState = new State("End", endValidCommands);


    //creating a vector of states
    std::vector<State*> gameStates={start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win, endState };

    for (int i = 0; i < gameStates.size(); i++)
        this->gameStates.push_back(gameStates[i]);

    //Setting the current state to Start
    this->currentState=start;

    //Initializing the stateEnumToStringMap
    initializeEnumToStringMap();

    //Creating the CommandProcessor and filling it's valid commands using the updateCmdProcessor() function
    CommandProcessor* cmdProcessor = new CommandProcessor();
    this->cmdProcessor = cmdProcessor;
    updateCmdProcessor();

    //Creating the game deck
    this->gameDeck = new Deck();


    
}

// Destructor - GameEngine
GameEngine::~GameEngine()
{
    //Deleting the Command objects
    for (Command* c : gameCommands) {
        delete c;
    }

    //Deleting the State objects
    for (State* s : gameStates) {
        delete s;
    }

    //Deleting the player objects
    for (Player* s : playerList) {
        delete s;
    }
        
    delete cmdProcessor;
	delete activeMap;
    delete gameDeck;
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
    out << "[Current state of the game:" << gameEngine.currentState << " ]" << std::endl;

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
        std::cout << "The entered command is invalid for the current state: " << this->currentState->name << std::endl;
        return false;
    }
   //std::cout << "The entered command is valid!" << std::endl;
   
   // Calling the map to get the number of the state
   stateNumber=enumToStringMapHandling(stringUnifier(this->currentState->name));

   // Checking if the state number is found in map
   if (stateNumber == -1)
       return false;

   // call transition to change gamestate
   transitionState(this, stateNumber, input);
   return true;
}

//Implements a command-based user inteaction mechanism for the game start 
void GameEngine::startupPhase() {
    //checks for the loadmap command
	std::string mapsPath = "C:/ProjectSchool/COMP 345/COMP345/PeaceZone/Map/ConquestMaps";
	std::vector<std::string> mapsFileNames;
    std::string filePathName;
    Command* currentCommand;
    MapLoader* mapLoader = new MapLoader();

	for (const auto& entry : std::experimental::filesystem::directory_iterator(mapsPath))
	{
        filePathName = entry.path().u8string();
		size_t lastdot = filePathName.find_last_of(".");
		size_t lastslash = filePathName.find_last_of("\\");
        mapsFileNames.push_back(filePathName.substr(lastslash + 1, lastdot));
	}
	std::cout << "Welcome to the PeaceZone startup phase." << std::endl;
	std::cout << "The following map files has been found in the conquestMaps directory: " << std::endl;
	for (std::string fileName : mapsFileNames) {
		std::cout << fileName << std::endl ;
	}
    
    //User must enter a valid fileName
    bool isValid = false;
    bool hasActiveMap = false;
    // Loop for map loading and validation
    do{
        std::cout << std::endl << "Please use the loadmap <filename> command to select the map that will be loaded to the game. " << std::endl;
        // Loop for map loading
        do{
            std::cout << "You are currently in the State: " << this->currentState->name << std::endl;
            currentCommand = this->cmdProcessor->getCommand();
            
            //verify the syntax
            std::string errorCheck = "Error";
        
            if (currentCommand->effect.find(errorCheck) != std::string::npos)
            {
                std::cout << currentCommand->effect << std::endl;
                continue;
            }

            if (currentCommand->name._Equal("validatemap"))
            {
                break;
            }
            

            //verify if the fileName is present in directory
            for (std::string fileName : mapsFileNames) {
                if (currentCommand->name._Equal("loadmap " + fileName))
                {
                
                    std::cout << "Command successfull, attempting to load the map..." <<std::endl;
                    //load map

                    mapLoader->Load(mapsPath + "/"+ fileName);
                    
                    if (mapLoader->maps.size() == 0){
						std::cout << "Failed to load map file " << mapsPath << "/" << fileName << std::endl;
                        currentCommand->saveEffect("Failed to load map file " + mapsPath + "/" + fileName);
                        break;
                    }
                    
				    activeMap = mapLoader->maps[0];
                    hasActiveMap = true;
                    
                    currentCommand->saveEffect(fileName+" map loaded");
                 
                    std::cout << "Enter the command \"loadmap <filename>\" to load another map or the command \"validatemap\" to validate the current loaded map" << std::endl;

                    checkCommandValidity("loadmap");

                    break;
				    
                
                }
            }
        } while (!currentCommand->name._Equal("validatemap") || !hasActiveMap);
		
		std::cout << "Now validating map " << activeMap->name << "..."<< std::endl;
        //validating map
		isValid = activeMap->Validate();
        if (!isValid){
			std::cout << "The map you have entered is invalid. Please try again with a different map. " << std::endl;
            delete mapLoader->maps[0];
            activeMap = NULL;
            currentCommand->saveEffect("The loaded map is invalid.");
            continue;
        }
		checkCommandValidity("validatemap");

    } while (!isValid);

    //map is validated

    //ADDING PLAYERS
	std::cout << "Map has been successfully validated! Transitioning to state " << this->currentState->name << "." << std::endl << std::endl;
    currentCommand->saveEffect("Map has been successfully validated!");
    std::cout << "Please use the command \"addplayer\" to add 2-6 players " << std::endl << std::endl;
    do{
        std::cout << "You currently have " << this->playerList.size() << " players. " << std::endl << std::endl;
		currentCommand = this->cmdProcessor->getCommand();

		//verify the syntax
		std::string errorCheck = "Error";

		if (currentCommand->effect.find(errorCheck) != std::string::npos)
		{
			std::cout << currentCommand->effect << std::endl;
			std::cout << "You are currently in the State:" << this->currentState->name << std::endl << std::endl;
			continue;
		}

		if (currentCommand->name._Equal("gamestart"))
		{
			continue;
		}

        //single out the name

		std::string space = " ";
		std::string inputCommand = currentCommand->name.substr(0, currentCommand->name.find(space));
		std::string name = currentCommand->name.substr(currentCommand->name.find(space) + 1, currentCommand->name.size());

        if(inputCommand._Equal("addplayer") && this->playerList.size() == 6){
			std::cout << "You cannot add more players, since you are at " << this->playerList.size() << " players. Please use \"gamestart\" to start the game." << std::endl << std::endl;
            continue;
        }


        this->addPlayer(name);
		
		checkCommandValidity("addplayer");
        currentCommand->saveEffect("Player " + name + " Added to the list of player.");

		std::cout << "Enter the command \"addplayer <playername>\" to add another player or the command \"gamestart\" to start the game" << std::endl;
		std::cout << "You are currently in the State: " << this->currentState->name << std::endl << std::endl;
		
    } while (!currentCommand->name._Equal("gamestart")||this->playerList.size() < 2 || this->playerList.size() > 6);

    currentCommand->saveEffect("The game has started.");

    //fairly distribute all the territories to the players 

    //shuffle the territories in the map object
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(this->activeMap->territories), std::end(this->activeMap->territories), rng);

    //Distribute territories to players
    int numberOfTerritoriesPerPlayer = std::floor(this->activeMap->territories.size() / this->playerList.size());
    int territoriesCount = 0;
    

    for (Player* player : this->playerList) 
    {
        for (int i = 0; i < numberOfTerritoriesPerPlayer; i++) 
        {
            player->addPlayerTerritories(this->activeMap->territories[territoriesCount++]);
        }
    }
    int nbOfLeftOverTerritories = this->activeMap->territories.size() - territoriesCount;
    //In the case of left-over territories
    if (nbOfLeftOverTerritories>0){
        for (int i = 0; i < nbOfLeftOverTerritories; i++) {

			playerList[i]->addPlayerTerritories(this->activeMap->territories[territoriesCount++]);
        }
    }

    //Print players territories
	std::cout << "Printing players' territories: " << std::endl;

    for (Player* player : this->playerList) {
        std::cout << *player << std::endl;
    }


	std::cout << "Done printing players' territories: " << std::endl;
    std::cout << "=====" << std::endl << std::endl;
    // Determining order of players
	auto rngOrder = std::default_random_engine{};
	std::shuffle(std::begin(this->playerList), std::end(this->playerList), rngOrder);

    // Give 50 initial army units to the players, which are placed in their respective reinforcement pool
	for (Player* player : this->playerList)
	{
        player->setReinforcementPool(50);
		
	}
    std::cout << "An initial reinforcement pool of 50 army unit has been given to each player " << std::endl;

    //Each player is drawing 2 initial cards from the deck 

    for (Player* player : this->playerList)
    {
        Hand* handOfCard = new Hand();
        handOfCard->Insert(this->gameDeck->Draw());
        handOfCard->Insert(this->gameDeck->Draw());
        player->setPlayerHandOfCards(handOfCard);

    }
    std::cout << "Two initial cards has been given to each player.  " << std::endl;
    std::cout << "Now let the game start! Printing players' information:" << std::endl;

    for (Player* player : this->playerList) {
        std::cout << *player << std::endl;
    }

	checkCommandValidity("gamestart");
}
 
//Method that updates the commandProcessor validCommands
void GameEngine::updateCmdProcessor() {
    this->cmdProcessor->validCommands = this->currentState->validCommands;

}

//Method that adds players 
void GameEngine::addPlayer(std::string name) 
{
    Player* player = new Player(name);

    this->playerList.push_back(player);
    std::cout << "Player " << name << " added to the game player list." <<std::endl;

}

void GameEngine::chooseInputMode(std::string mode) {

    if (mode.find("file") != std::string::npos) {

        std::string space = " ";
        std::string fileString = mode.substr(0, mode.find(space));
        std::string path = mode.substr(mode.find(space) + 1, mode.size());

        // std::string path("C:/ProjectSchool/COMP 345/COMP345/PeaceZone/GameEngine/GameStartupCommands.txt");

        FileLineReader* flr = new FileLineReader(path);
        FileCommandProcessorAdapter* fcpa = new FileCommandProcessorAdapter(this->cmdProcessor->commandList, this->cmdProcessor->validCommands, flr);

        this->cmdProcessor = fcpa;

        std::cout << "Game engine is now using FileCommandProcessorAdaptor." << std::endl << std::endl;
    }
    else if (mode._Equal("console")) 
    {
        std::cout << "Game engine is now using CommandProcessor." << std::endl << std::endl;

    }
}
#pragma endregion


#pragma region Helpers

static const enum stateNames { start, maploaded, mapvalidated, playersadded, assignreinforcement, issueorders, executeorders, win, endState=8};


//Helper function used to unify strings
extern std::string stringUnifier(std::string input) 
{
    // To lower case
    std::for_each(input.begin(), input.end(), [](char& c) {
        c = ::tolower(c);
        });
    std::regex r("\\s+");
    // Remove spaces
    input = std::regex_replace(input, r, "");
    return input;

}
// Initializing the enum to string map
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


}
// Handling the map 
 int enumToStringMapHandling(std::string input)
{
     return (stateEnumToStringMap[input]);
}

#pragma endregion