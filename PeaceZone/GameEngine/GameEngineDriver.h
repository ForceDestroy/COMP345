#pragma once
#include "GameEngine.h";
#include <algorithm>

class GameEngineDriver {
public:
	static State* testGameStates(std::string transition, State* currentState);

private:
	// Transition methods for testGameStates

	// Start State Transition
	static Transition* startStateTransition(std::string transition, State* currentState);

    // Start State Transition
	static Transition* mapLoadedStateTransition(std::string transition, State* currentState);

    // Start State Transition
    static Transition* mapValidatedStateTransition(std::string transition, State* currentState);

    // Start State Transition
    static Transition* playersAddedStateTransition(std::string transition, State* currentState);

    // Start State Transition
    static Transition* assignReinforcementStateTransition(std::string transition, State* currentState);

    // Start State Transition
    static Transition* issueOrdersStateTransition(std::string transition, State* currentState);

    // Start State Transition
    static Transition* executeOrdersStateTransition(std::string transition, State* currentState);

    // Start State Transition
    static Transition* winStateTransition(std::string transition, State* currentState);

};
