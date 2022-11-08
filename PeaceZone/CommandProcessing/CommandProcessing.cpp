#include "CommandProcessing.h"

#pragma region CommandProcessing
// Default Constructor - Command
CommandProcessor::CommandProcessor() = default;

// Destructor - Command
CommandProcessor::~CommandProcessor() = default;

//Constructor - Command
CommandProcessor::CommandProcessor(std::vector<Command*> commandList)
{
	this->commandList = commandList;
}

//Copy constructor - Command
CommandProcessor::CommandProcessor(const CommandProcessor &c1)
{
	this->commandList = c1.commandList;
}

// Assignment Operator - Command
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &c1)
{
	this->commandList = c1.commandList;

	return *this;
}

// Stream Insertion Operator - Command
std::ostream& operator<<(std::ostream &out, const CommandProcessor &commandProcesssor)
{
	for (int i = 0; i <  commandProcesssor.commandList.size(); i++)
		out << *commandProcesssor.commandList[i] << " ";
	out << "}";
	return out;
}

//public getCommand() method
Command* CommandProcessor::getCommand(GameEngine* gameEngine)
{
	std::string commandName = readCommand();
	Command* command = new Command(commandName, "");
	validate(gameEngine, command);
	saveCommand(command);
	return command;
	
}


//private saveCommand() method
void CommandProcessor::saveCommand(Command* command)
{
	this->commandList.push_back(command);

}

//validate() method
void CommandProcessor::validate(GameEngine* gameEngine, Command* command)
{
	// vector comparing
	int count = 0;
	int stateNumber = -1;
	std::string output = "";

	for (int i = 0; i < gameEngine->currentState->validCommands.size(); i++)
	{
		if (gameEngine->currentState->validCommands[i]->name._Equal(command->name)) {
			count++;
		}
	}

	if (count != 1) {
		output = "Error: The entered command (" + command->name + ") is invalid for the current state: " + gameEngine->currentState->name;
		command->saveEffect(output);
	}


}

//private readCommand() method
std::string CommandProcessor::readCommand()
{
	std::cout << "Please enter a valid command for the current state : " << std::endl;

	std::string input;
	std::getline(std::cin,input);
	std::string cleanInput = stringUnifier(input);
	return cleanInput;

}



#pragma endregion


#pragma region FileCommandProcessorAdapter

#pragma endregion

#pragma region FileLineReader

#pragma endregion