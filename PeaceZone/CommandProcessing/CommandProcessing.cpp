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

// Save the effect of a command as a string in a Command object
void Command::saveEffect(std::string effect)
{
	this->effect = effect;
	Notify(this);
}

std::string Command::stringToLog()
{
	std::string log = "LOG::Command:: Save Command Effect - " + this->effect;
	return log;
}

#pragma endregion

#pragma region CommandProcessing
// Default Constructor - CommandProcessor
CommandProcessor::CommandProcessor() = default;

// Destructor - CommandProcessor
CommandProcessor::~CommandProcessor(){
	//Deleting the Command objects in the list of commands
	for (Command* c : commandList) {
        delete c;
		c=NULL;
    }

	
};

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

//Public command method that can be called by other object to get a command.
// It reads the command, create a Command object, validate it and save it to the list of commands. 
Command* CommandProcessor::getCommand()
{
	std::string commandName = readCommand();
	Command* command = new Command(commandName, "");
	validate(command);
	saveCommand(command);
	return command;
}

//Public command method that can be called by other object to get a command.
// It reads the command, create a Command object, validate it and save it to the list of commands. 
Command* CommandProcessor::getCommand(std::string commandName)
{
	Command* command = new Command(commandName, "");
	validate(command);
	saveCommand(command);
	return command;
}


//Saves the command object into the list of commands
void CommandProcessor::saveCommand(Command* command)
{
	this->commandList.push_back(command);
	Notify(this);
}

//Checks if a given command is valid by comparing it to the vector of valid commands. 
//The vector of valid commands is handled by the GameEngine and is updated for every state change. 
void CommandProcessor::validate(Command* command)
{
	// vector comparing
	int count = 0;
	int stateNumber = -1;
	std::string output = "";

	for (int i = 0; i < this->validCommands.size(); i++)
	{
		if (this->validCommands[i]->name._Equal(command->name) && !command->name._Equal("loadmap") && !command->name._Equal("addplayer") && !command->name._Equal("tournament") ){
			count++;
		}else{
			std::string space = " ";
			std::string inputCommand = command->name;
			std::string restOfCommand = "";

			if (command->name.find(space) != std::string::npos) {
				inputCommand = command->name.substr(0, command->name.find(space));
				restOfCommand = command->name.substr(command->name.find(space) + 1, command->name.size());

			}
			
			//validating commands loadmap <mapfile> 
			if (this->validCommands[i]->name._Equal(inputCommand) && (inputCommand._Equal("loadmap") && restOfCommand.find(space) == std::string::npos && !restOfCommand._Equal(""))) {
				count++;
				output = "Command " + command->name + " is valid for the current state";
				command->saveEffect(output);
			}
			else if(inputCommand._Equal("loadmap") && restOfCommand.find(space) != std::string::npos) {
				output = "Error: Invalid loadmap <mapfile> command (" + command->name + "). Only one map file name must be entered with the command. ";
				command->saveEffect(output);
				return;
			}
			else if (inputCommand._Equal("loadmap") && restOfCommand.empty()) {
				output = "Error: Invalid loadmap <mapfile> command (" + command->name + "). Rest of command is needed to load a map. ";
				command->saveEffect(output);
				return;
			}

			//validating commands addplayer <playername> 
			else if (this->validCommands[i]->name._Equal(inputCommand) && inputCommand._Equal("addplayer")) {
				count++;
				output = "Command " + command->name + " is valid for the current state";
				command->saveEffect(output);

			}else if(inputCommand._Equal("addplayer") && restOfCommand.empty()) {
				output = "Error: Invalid addplayer <playername> command (" + command->name + "). Rest of command is needed to add a player. ";
				command->saveEffect(output);
				return;

			}
			//validating commands tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>
			// tournament -M Alabama, Montreal, Canada -P Benevolent, Cheater, Aggressive -G 4 -D 50 

			else if (this->validCommands[i]->name._Equal(inputCommand) && inputCommand._Equal("tournament")) {

				if (restOfCommand.empty()) {
					output = "Error: Invalid tournament command (" + command->name + "). Rest of command is empty. Make sure it follows this format: tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns> ";
					command->saveEffect(output);
					return;
				}

				// Checking if all parameters are present
				if (restOfCommand.find("-M") != std::string::npos 
					&& restOfCommand.find("-P") != std::string::npos 
					&& restOfCommand.find("-G") != std::string::npos 
					&& restOfCommand.find("-D") != std::string::npos
					&& restOfCommand.find("-M") < restOfCommand.find("-P") < restOfCommand.find("-G") < restOfCommand.find("-D")) {

					std::string map = restOfCommand.substr(restOfCommand.find("-M ") + 3, restOfCommand.find("-P") - (restOfCommand.find("-M ") + 3));
					std::string playerStrategies = restOfCommand.substr(restOfCommand.find("-P ") + 3, restOfCommand.find("-G")-(restOfCommand.find("-P ") + 3));
					std::string games = restOfCommand.substr(restOfCommand.find("-G ") + 3, restOfCommand.find("-D") - (restOfCommand.find("-G ") + 3));
					std::string turns = restOfCommand.substr(restOfCommand.find("-D ") + 3, restOfCommand.size() - restOfCommand.find("-D ") + 3);

					/*std::cout << "Map: " << map << std::endl;
					std::cout << "Player Strategies: " << playerStrategies << std::endl;
					std::cout << "Games: " << games << std::endl;
					std::cout << "Turns: " << turns << std::endl;*/

					// Validating each parameter is of correct format: 
					// Validating map
					std::vector<std::string> mapList;
					std::string delimiter = ", ";
					size_t pos = 0;
					std::string token;
					while ((pos = map.find(delimiter)) != std::string::npos) {
						token = map.substr(0, pos);
						mapList.push_back(token);
						map.erase(0, pos + delimiter.length());
					}

					map.pop_back();
					mapList.push_back(map);

					if (1 > mapList.size() || mapList.size() > 5) {
						output = "Error: Invalid tournament command (" + command->name + "). You have either too many maps (more than 5) or not enough maps (less than 1). ";
						command->saveEffect(output);
						return;
					}

					// Validating player strategies
					std::vector<std::string> strategiesList;
					delimiter = ", ";
					pos = 0;
					token = "";

					

					while ((pos = playerStrategies.find(delimiter)) != std::string::npos) {
						token = playerStrategies.substr(0, pos);
						strategiesList.push_back(token);
						playerStrategies.erase(0, pos + delimiter.length());
					}

					playerStrategies.pop_back();
					strategiesList.push_back(playerStrategies);

					if (2 > strategiesList.size() || strategiesList.size() > 4) {
						output = "Error: Invalid tournament command (" + command->name + "). You have either too many strategies (more than 4) or not enough strategies (less than 2). Strategies seen:  ";
						for (std::string strategy : strategiesList) {
							output += strategy + ", ";
							//std::cout << strategy << std::endl;
						}
						command->saveEffect(output);
						return;
					}

					for (std::string strategy : strategiesList) {
						if (!(strategy._Equal("Aggressive") || strategy._Equal("Benevolent") || strategy._Equal("Neutral") || strategy._Equal("Cheater"))) {
							output = "Error: Invalid tournament command (" + command->name + "). Strategy " + strategy + " is not part of the valid strategies: Aggressive, Benevolent, Neutral, Cheater.";
							command->saveEffect(output);
							return;
						}
					}

					// Validating number of games

					int gamesInt = stoi(games);
					if (1 > gamesInt || gamesInt > 5) {
						output = "Error: Invalid tournament command (" + command->name + "). You have either too many games (more than 5) or not enough games (less than 1). ";
						command->saveEffect(output);
						return;

					}

					// Validating max of number of turns

					int turnsInt = stoi(turns);
					if (10 > turnsInt || turnsInt > 50) {
						output = "Error: Invalid tournament command (" + command->name + "). You have either too many turns (more than 50) or not enough turns (less than 10). ";
						command->saveEffect(output);
						return;

					}

					// Everything passed
					count++;
					output = "Command " + command->name + " is valid for the current state";
					command->saveEffect(output);


				}
				else {
					output = "Error: Invalid tournament command (" + command->name + "). Missing a parameter for the tournament command. Make sure it follows this format: tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns> ";
					command->saveEffect(output);
					return;
				}
			}
		}
	}

	if (count != 1) {
		output = "Error: The entered command (" + command->name + ") is invalid for the current state";
		command->saveEffect(output);
	}


}

std::string CommandProcessor::stringToLog()
{
	std::string log = "LOG::CommandProcessor:: Command Entered - " + this->commandList.back()->name;
	return log;
}

//private readCommand() method that gets a command from the console and returns it as a string. 
std::string CommandProcessor::readCommand()
{
	std::cout << std::endl << "Please enter a valid command for the current state : " << std::endl << "<<<<<<<<<<<<<<<<<<<<<" << std::endl;

	std::string input;
	std::getline(std::cin,input);
	//std::string cleanInput = stringUnifier(input);

	std::cout << "<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl;
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

//Method that use the class's fileStream to read a line from the file and returns it as a string
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

//Method that takes a file path and open a fileStream 
void FileLineReader::setPath(std::string path)
{
	this->path = path;
	//open a file to perform read operation using file object
	fileStream.open(this->path, std::ios::in); 
}

#pragma endregion

#pragma region FileCommandProcessorAdapter
// Default Constructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter::FileCommandProcessorAdapter() = default;

// Destructor - FileCommandProcessorAdapter
FileCommandProcessorAdapter :: ~FileCommandProcessorAdapter(){
	delete flr;
	flr=NULL;
};

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

//Overrides the readCommand() method of the CommandProcessor class
//Returns the string of a command by reading a line from a file
std::string FileCommandProcessorAdapter::readCommand(){
	
	std::cout << std::endl << "Reading command from file... " << std::endl;

	std::string input;

	input = this->flr->readLineFromFile();


	std::cout << "Finished reading from file. " << std::endl << std::endl;
	return input;
	

}
#pragma endregion
