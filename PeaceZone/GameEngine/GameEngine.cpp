#include "GameEngine.h"


#pragma region State
// Default Constructor - State
State::State() = default;

// Destructor - State
State::~State() = default;

//Constructor - State
State::State(std::string name,Command validCommands)
{
    this->name=name;
    this->validCommands=validCommands;
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
    out << "{ Name: " << state.name << ", valid commands: " << state.validCommands;

    return out;
}

#pragma endregion
