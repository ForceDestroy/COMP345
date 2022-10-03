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
Command::Command(const Command& c1)
{
    this->name = c1.name;
}

// Assignment Operator - Command
Command& Command::operator=(const Command& c1)
{
    this->name = c1.name;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Command& command)
{
    out << "{ Name: " << command.name << " }";

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
    out << "{ Name: " << state.name << ", valid commands: ";
    out << "{ validCommands: \n";
    for (int i = 0; i < state.validCommands.size(); i++)
        out << state.validCommands[i] << "\n";
    return out;
}

#pragma endregion
