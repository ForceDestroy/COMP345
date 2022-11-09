#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <fstream>


#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

class Command {
public:
	// Data Members
	std::string name;
	std::string effect;
	

	// Constructors
	Command();
	Command(std::string name);
	Command(std::string name, std::string effect);
	Command(const Command& c1);
	~Command();

	// Methods
	Command& operator=(const Command&);
	friend std::ostream& operator<<(std::ostream& out, const Command& Command);

	//saveEffect() method
	void saveEffect(std::string effect);


};

class CommandProcessor {
public:
    // Data Members
    std::vector<Command*> commandList;
    std::vector<Command*> validCommands;

    // Constructors
    CommandProcessor();
    CommandProcessor(std::vector<Command*> commandList);
    CommandProcessor(const CommandProcessor& c1);
    ~CommandProcessor();

    // Methods
    CommandProcessor& operator=(const CommandProcessor&);
    friend std::ostream& operator<<(std::ostream& out, const CommandProcessor& commandProcessor);

    //public getCommand() method
    Command* getCommand(std::vector<Command*> validCommands, std::string mode);

    
   
    //validate() method
    void validate(std::vector<Command*> validCommandss, Command* command);

private: 
    //private readCommand() method
    std::string readCommand(std::string mode);

	//saveCommand() method
	void saveCommand(Command* command);

   
};

//In charge of reading the file line by line
class FileLineReader {
public:
    // Data Members
    std::string path;


    // Constructors
    FileLineReader();
	FileLineReader(std::string name);
    FileLineReader(const FileLineReader& fileLineReader1);
    ~FileLineReader();

    // Methods
    FileLineReader& operator=(const FileLineReader&);
    friend std::ostream& operator<<(std::ostream& out, const FileLineReader& fileLineReader);

    std::string readLineFromFile();
    void setPath(std::string path);
};

class FileCommandProcessorAdapter :public CommandProcessor {
public:
    // Data Members
    FileLineReader* flr;

    // Constructors
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(FileLineReader* flr);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& c1);
    ~FileCommandProcessorAdapter();

    // Methods
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter&);
    friend std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter& FileCommandProcessorAdapter);

    //readCommand() method
    std::string readCommand(std::string mode);
};

// Free function for game state testings
static void testCommandProcessor(std::vector<Command*> validCommands);
