#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>

#include "../LoggingObserver/LoggingObserver.h"

#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

class Command : public ILoggable, public Subject {
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

    std::string stringToLog() override;
};

class CommandProcessor : public ILoggable, public Subject {
public:
    // Data Members
    std::vector<Command*> commandList;
    std::vector<Command*> validCommands;

    // Constructors
    CommandProcessor();
    CommandProcessor(std::vector<Command*> commandList, std::vector<Command*> validCommands);
    CommandProcessor(const CommandProcessor& c1);
    ~CommandProcessor();

    // Methods
    CommandProcessor& operator=(const CommandProcessor&);
    friend std::ostream& operator<<(std::ostream& out, const CommandProcessor& commandProcessor);

    //public getCommand() method
    Command* getCommand();

    //validate() method
    void validate( Command* command);

	void saveCommand(Command* command);
    std::string stringToLog() override;

private: 
    //private readCommand() method
    virtual std::string readCommand();

	//saveCommand() method

   
};

//In charge of reading the file line by line
class FileLineReader {
public:
    // Data Members
    std::string path;
	std::fstream fileStream;


    // Constructors
    FileLineReader();
	FileLineReader(std::string path);
    FileLineReader(const FileLineReader& fileLineReader1);
    ~FileLineReader();

    // Methods
    FileLineReader& operator=(const FileLineReader&);
    friend std::ostream& operator<<(std::ostream& out, const FileLineReader& fileLineReader);

    std::string readLineFromFile();
    void setPath(std::string path);
};

//The Adapter Class FileCommandProcessorAdapter that inherits from the CommandProcessor class
class FileCommandProcessorAdapter : public CommandProcessor {
public:
    // Data Members
    FileLineReader* flr;

    // Constructors
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(std::vector<Command*> commandList, std::vector<Command*> validCommands, FileLineReader* theflr);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& c1);
    ~FileCommandProcessorAdapter();

    // Methods
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter&);
    friend std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter& FileCommandProcessorAdapter);
    
    //readCommand() method
    std::string readCommand() override;
};


