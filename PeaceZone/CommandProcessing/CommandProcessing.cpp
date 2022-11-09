#include "CommandProcessing.h"

#pragma region Command
// Default Constructor - Command
Command::Command() = default;

// Destructor - Command
Command::~Command() = default;

//Constructor - Command
Command::Command(std::string name)
{
	this->name = name;
	this->effect = "";
}

//Constructor - Command
Command::Command(std::string name, std::string effect)
{
	this->name = name;
	this->effect = effect;
}

//Copy constructor - Command
Command::Command(const Command& c1)
{
	this->name = c1.name;
	this->effect = c1.effect;
}

// Assignment Operator - Command
Command& Command::operator=(const Command& c1)
{
	this->name = c1.name;
	this->effect = c1.effect;
	return *this;
}

// Stream Insertion Operator - Command
std::ostream& operator<<(std::ostream& out, const Command& command)
{
	out << "[" << command.name << ", " << command.effect << " ]";

	return out;
}

void Command::saveEffect(std::string effect)
{
	this->effect = effect;
}

#pragma endregion

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
Command* CommandProcessor::getCommand(std::vector<Command*> validCommands, std::string mode)
{
	std::string commandName = readCommand(mode);
	Command* command = new Command(commandName, "");
	validate(validCommands, command);
	saveCommand(command);
	return command;
	
}


//private saveCommand() method
void CommandProcessor::saveCommand(Command* command)
{
	this->commandList.push_back(command);

}

//validate() method
void CommandProcessor::validate(std::vector<Command*> validCommands, Command* command)
{
	// vector comparing
	int count = 0;
	int stateNumber = -1;
	std::string output = "";

	for (int i = 0; i < validCommands.size(); i++)
	{
		if (validCommands[i]->name._Equal(command->name)) {
			count++;
		}else{
			std::string space = " ";
			std::string inputCommand = command->name.substr(0, command->name.find(space));
			std::string restOfCommand = command->name.substr(command->name.find(space) + 1, command->name.size());
			
			//validating commands loadmap <mapfile> and addplayer <playername> 
			if (validCommands[i]->name._Equal(inputCommand) && (inputCommand._Equal("loadmap") && restOfCommand.find(space) == std::string::npos) ){
				count++;
			}
			else if(inputCommand._Equal("addplayer")) {
				count++;

			}else if(inputCommand._Equal("loadmap") && restOfCommand.find(space) != std::string::npos) {
				output = "Error: Invalid loadmap <mapfile> command (" + command->name + "). Only one map file name must be entered with the command. ";
				command->saveEffect(output);
				return;
			}
		}
	}

	if (count != 1) {
		output = "Error: The entered command (" + command->name + ") is invalid for the current state";
		command->saveEffect(output);
	}


}

//private readCommand() method
std::string CommandProcessor::readCommand(std::string mode)
{
	if (mode._Equal("cmd")) {
		
		std::cout << "Please enter a valid command for the current state : " << std::endl;

		std::string input;
		std::getline(std::cin,input);
		//std::string cleanInput = stringUnifier(input);
		return input;
	}

	else {
		return "Error";
	}


}



#pragma endregion


#pragma region FileCommandProcessorAdapter
// Default Constructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter::FileCommandProcessorAdapter() = default;

// Destructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter :: ~FileCommandProcessorAdapter() = default;

// Constructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* flr) {
	this->flr = flr;
}

// Copy constructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& c1) {
	this->flr = flr;
}

// Assignment Operator - FileCommandProcessorAdapter
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& c1) {
	this->flr = c1.flr;
	return *this;
}

// Stream Insertion Operator - FileCommandProcessorAdapter
std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter &FileCommandProcessorAdapter)
{
	out << "FileCommandProcessorAdapter using the fileLineReader" << FileCommandProcessorAdapter.flr;
	return out;
}

std::string FileCommandProcessorAdapter::readCommand(std::string mode) {
	if (mode._Equal("file")) {
		std::cout << "Reading commands from file: " << std::endl;

		std::string input;
		input = flr->readLineFromFile();
		return input;
	}
	else {
		return "Error";
	}

}
#pragma endregion

#pragma region FileLineReader
// Default Constructor - FileLineReader
FileLineReader::FileLineReader() = default;

// Destructor - FileLineReader
FileLineReader :: ~FileLineReader() = default;

//Constructor - FileLineReader
FileLineReader::FileLineReader(std::string path)
{
	this->path = path;
}

//Copy constructor - FileLineReader
FileLineReader::FileLineReader(const FileLineReader& flr1)
{
	this->path = flr1.path;
}

// Assignment Operator - FileLineReader
FileLineReader& FileLineReader::operator=(const FileLineReader& c1) {
	this->path = c1.path;
	return *this;
}

// Stream Insertion Operator - FileCommandProcessorAdapter
std::ostream& operator<<(std::ostream& out, const FileLineReader& fileLineReader)
{
	out << "FileLineReader is using the file " << fileLineReader.path;
	return out;
}

std::string FileLineReader::readLineFromFile() {
	
	std::fstream newfile;
	std::string input;

	newfile.open(this->path, std::ios::in); //open a file to perform read operation using file object
	if (newfile.is_open()) {   //checking whether the file is open
		
		while (getline(newfile, input)) { //read data from file object and put it into string.
			std::cout << input << std::endl; //print the data of the string
		}
		newfile.close(); //close the file object.
	}
	return input;
}

void FileLineReader::setPath(std::string path)
{
	this->path = path;
}

#pragma endregion