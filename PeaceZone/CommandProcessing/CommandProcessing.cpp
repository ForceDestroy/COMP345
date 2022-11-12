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
// Default Constructor - CommandProcessor
CommandProcessor::CommandProcessor() = default;

// Destructor - CommandProcessor
CommandProcessor::~CommandProcessor() = default;

//Constructor - CommandProcessor
CommandProcessor::CommandProcessor(std::vector<Command*> commandList, std::vector<Command*> validCommands)
{
	this->commandList = commandList;
	this->validCommands = validCommands;
}

//Copy constructor - CommandProcessor
CommandProcessor::CommandProcessor(const CommandProcessor &c1)
{
	this->commandList = c1.commandList;
}

// Assignment Operator - CommandProcessor
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &c1)
{
	this->commandList = c1.commandList;

	return *this;
}

// Stream Insertion Operator - CommandProcessor
std::ostream& operator<<(std::ostream &out, const CommandProcessor &commandProcesssor)
{
	out << "Command list: {";

	for (int i = 0; i <  commandProcesssor.commandList.size(); i++)
		out << *commandProcesssor.commandList[i] << " ";
	out << "}" << std::endl;

	out << "Current valid commands: {";

	for (int i = 0; i < commandProcesssor.validCommands.size(); i++)
		out << *commandProcesssor.validCommands[i] << " ";
	out << "}";

	return out;
}

//public getCommand() method
Command* CommandProcessor::getCommand()
{
	std::string commandName = readCommand();
	Command* command = new Command(commandName, "");
	validate(command);
	saveCommand(command);
	return command;
	
}


//private saveCommand() method
void CommandProcessor::saveCommand(Command* command)
{
	this->commandList.push_back(command);

}

//validate() method
void CommandProcessor::validate(Command* command)
{
	// vector comparing
	int count = 0;
	int stateNumber = -1;
	std::string output = "";

	for (int i = 0; i < this->validCommands.size(); i++)
	{
		if (this->validCommands[i]->name._Equal(command->name)) {
			count++;
		}else{
			std::string space = " ";
			std::string inputCommand = command->name.substr(0, command->name.find(space));
			std::string restOfCommand = command->name.substr(command->name.find(space) + 1, command->name.size());
			
			//validating commands loadmap <mapfile> and addplayer <playername> 
			if (this->validCommands[i]->name._Equal(inputCommand) && (inputCommand._Equal("loadmap") && restOfCommand.find(space) == std::string::npos) ){
				count++;
				output = "Command " + command->name + " is valid for the current state";
				command->saveEffect(output);
			}
			else if(this->validCommands[i]->name._Equal(inputCommand) && inputCommand._Equal("addplayer")) {
				count++;
				output = "Command " + command->name + " is valid for the current state";
				command->saveEffect(output);

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
std::string CommandProcessor::readCommand()
{
	std::cout << std::endl << "Please enter a valid command for the current state : " << std::endl;

	std::string input;
	std::getline(std::cin,input);
	//std::string cleanInput = stringUnifier(input);
	return input;
	
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
	fileStream.open(this->path, std::ios::in); //open a file to perform read operation using file object
}

//Copy constructor - FileLineReader
FileLineReader::FileLineReader(const FileLineReader& flr1)
{
	this->path = flr1.path; 
	fileStream.open(flr1.path, std::ios::in); //open a file to perform read operation using file object
}

// Assignment Operator - FileLineReader
FileLineReader& FileLineReader::operator=(const FileLineReader& c1) {
	this->path = c1.path;
	this->fileStream.open(c1.path, std::ios::in); //open a file to perform read operation using file object
	return *this;
}

// Stream Insertion Operator - FileCommandProcessorAdapter
std::ostream& operator<<(std::ostream& out, const FileLineReader& fileLineReader)
{
	out << "FileLineReader is using the file " << fileLineReader.path;
	return out;
}

std::string FileLineReader::readLineFromFile()
{

	std::string input;
	int count;

	if (fileStream.is_open()) {   //checking whether the file is open
		try
		{
			std::getline(fileStream, input); //read data from file object and put it into string.
			std::cout << "The following input has been read from the file : " << input << std::endl; //print the data of the string
		}
		catch (...)
		{
			std::cout << "fstream did not get line";
		}
	

	}


	return input;
}

void FileLineReader::setPath(std::string path)
{
	this->path = path;

	fileStream.open(this->path, std::ios::in); //open a file to perform read operation using file object
}

#pragma endregion

#pragma region FileCommandProcessorAdapter
// Default Constructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter::FileCommandProcessorAdapter() = default;

// Destructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter :: ~FileCommandProcessorAdapter() = default;

// Constructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter::FileCommandProcessorAdapter(std::vector<Command*> commandList, std::vector<Command*> validCommands, FileLineReader* theflr) : CommandProcessor(commandList, validCommands), flr(theflr)
{

}

// Copy constructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& c1) : CommandProcessor(c1)  
{
	this->flr = c1.flr;
}

// Assignment Operator - FileCommandProcessorAdapter
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& c1) 
{
	CommandProcessor::operator=(c1);
	this->flr = c1.flr;
	return *this;
}

// Stream Insertion Operator - FileCommandProcessorAdapter
std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter &FileCommandProcessorAdapter)
{
	out << "From FileCommandProcessorAdapter:" << std::endl;
	
	out << "Command list: {";

	for (int i = 0; i < FileCommandProcessorAdapter.commandList.size(); i++)
		out << *FileCommandProcessorAdapter.commandList[i] << " ";
	out << "}" << std::endl;
	out << "Current valid commands: {";

	for (int i = 0; i < FileCommandProcessorAdapter.validCommands.size(); i++)
		out << *FileCommandProcessorAdapter.validCommands[i] << " ";
	out << "}";

	return out;
}

std::string FileCommandProcessorAdapter::readCommand(){
	
	std::cout << std::endl << "Reading command from file... " << std::endl;

	std::string input;

	input = this->flr->readLineFromFile();


	std::cout << "Finished reading from file. " << std::endl << std::endl;
	return input;
	

}
#pragma endregion
