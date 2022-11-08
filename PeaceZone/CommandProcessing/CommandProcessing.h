#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include "../GameEngine/GameEngine.h"



#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


class CommandProcessor {
public:
    // Data Members
    std::vector<Command*> commandList;

    // Constructors
    CommandProcessor();
    CommandProcessor(std::vector<Command*> commandList);
    CommandProcessor(const CommandProcessor& c1);
    ~CommandProcessor();

    // Methods
    CommandProcessor& operator=(const CommandProcessor&);
    friend std::ostream& operator<<(std::ostream& out, const CommandProcessor& commandProcessor);

    //public getCommand() method
    Command* getCommand(GameEngine* gameEngine);

    
   
    //validate() method
    void validate(GameEngine* gameEngine, Command* command);

private: 
    //private readCommand() method
    std::string readCommand();

	//saveCommand() method
	void saveCommand(Command* command);

   
};

//In charge of reading the file line by line
class FileLineReader {
public:
    // Data Members

    // Constructors
    FileLineReader();
    FileLineReader(const FileLineReader& fileLineReader1);
    ~FileLineReader();

    // Methods
    FileLineReader& operator=(const FileLineReader&);
    friend std::ostream& operator<<(std::ostream& out, const FileLineReader& fileLineReader);


};

class FileCommandProcessorAdapter {
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


    //getCommand() method


    //saveCommand() method

    void saveCommand();


    //validate() method
};

// Free function for game state testings
static void testCommandProcessor(GameEngine* gameEngine);
