#include "GameEngine.h"
#include "GameEngineDriver.h";

State* GameEngineDriver::testGameStates(std::string command, State* currentState) // Could change parameters to be transition?
{ 
    // String manipulation
    std::for_each(command.begin(), command.end(), [](char& c) {
        c = ::tolower(c);
        });


    // Command Filtering
    Transition* newTransition = NULL;

    if (command._Equal("start")) {
        // Start function
        
        newTransition = startStateTransition(command, currentState);
    }
    else if (command._Equal("loadmap")) {
        // Load Map Function

    }
    else if (command._Equal("validatemap")) {
        // Validate Map Function
    }
    else if (command._Equal("addplayer")) {
        // Add Player Function
    }
    else if (command._Equal("assigncountries")) {
        // Assign Countries Function
    }
    else if (command._Equal("issueorder")) {
        // Issue Order Function
    }
    else if (command._Equal("endissueorders")) {
        // End Issue Orders Function
    }
    else if (command._Equal("execorder")) {
        // Execute Order Function
    }
    else if (command._Equal("endexecorders")) {
        // End Execute Orders Function
    }
    else if (command._Equal("win")) {
        // Win Function
    }
    else if (command._Equal("play")) {
        // Play Again Function
    }
    else if (command._Equal("end")) {
        // End Function
    }

    else {
        // No valid command
       
        return NULL;
    }

    /*std::string command1 = "load map";
    std::string command2 = "validate map";
    Command* com1 = new Command(command1);
    Command* com2 = new Command(command2);
    std::vector<Command*> validCommands = {com1, com2};
    std::string start="start";
    State* s1=new State(command, validCommands);*/
    
    State* newState = newTransition->currentState;
    return newState;

   //delete com1;
   //delete com2; 

}


// Start State Transition
Transition* GameEngineDriver::startStateTransition(std::string transition, State* currentState) {
    // Setup
    std::string command1 = "loadmap";
    Command* com1 = new Command(command1);
    std::vector<Command*> currentValidCommands = { com1 };

    // Testing
    Command* comTest = new Command(transition);
    
    int count = 1;
    /*for (Command* c : currentValidCommands)
    {
        if (std::find(currentValidCommands.begin(), currentValidCommands.end(), currentValidCommands.size()) != currentValidCommands.end()) {
            count++;
        }

    }*/
    // If Fail
    if (count > currentValidCommands.size()) {
        return NULL;
        delete com1;
    }
    // Transition creation
    std::string newCommand1 = "loadmap";
    std::string newCommand2 = "validatemap";
    Command* newCom1 = new Command(newCommand1);
    Command* newCom2 = new Command(newCommand2);
    std::vector<Command*> newValidCommands = { newCom1, newCom2 };
    std::string newStateName = "maploaded";
    State* newState = new State(newStateName, newValidCommands);
    Transition* t1 = new Transition(newStateName, newState);

    return t1;

    delete com1;
    delete newCom1;
    delete newCom2;
}

//// Load Map State Transition
//Transition* mapLoadedStateTransition(std::string transition, State* currentState) {
//
//}
//
//// Map Validated State Transition
//Transition* mapValidatedStateTransition(std::string transition, State* currentState) {
//
//}
//
//// Players Added State Transition
//Transition* playersAddedStateTransition(std::string transition, State* currentState) {
//
//}
//
//// Assign Reingorcement State Transition
//Transition* assignReinforcementStateTransition(std::string transition, State* currentState) {
//
//}
//
//// Issue Orders State Transition
//Transition* issueOrdersStateTransition(std::string transition, State* currentState) {
//
//}
//
//// Execute Orders State Transition
//Transition* executeOrdersStateTransition(std::string transition, State* currentState) {
//
//}
//
//// Win State Transition
//Transition* winStateTransition(std::string transition, State* currentState) {
//
//}
