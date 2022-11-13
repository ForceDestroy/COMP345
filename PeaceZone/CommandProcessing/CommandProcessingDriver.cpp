#include "../GameEngine/GameEngine.h"
#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif
#define ever (;;)


void testCommandProcessor()
{
	//use the following command to test CommandProcessorAdapter
	//file C:/ProjectSchool/COMP 345/COMP345/PeaceZone/CommandProcessing/CommandProcessorCommands.txt
	//file C:/Users/Mimi/Documents/GitHub/COMP345/PeaceZone/CommandProcessing/CommandProcessorCommands.txt

	GameEngine* gameEngine = new GameEngine();

	//Choosing input mode and creating the right CommandProcessor
	gameEngine->chooseInputMode();
	std::string continueTesting;
	std::string errorCheck = "Error";
	Command* currentCommand;
	std::string commandString;
	std::string space = " ";
	
	do {
		std::cout <<std::endl << "The current state of the game is " << gameEngine->currentState->name ;
		currentCommand=gameEngine->cmdProcessor->getCommand();
		commandString = currentCommand->name.substr(0, currentCommand->name.find(space));
		//check is the command is valid
		if (currentCommand->effect.find(errorCheck) == std::string::npos) {
			std::string pastState = gameEngine->currentState->name;
			//update the state if valid
			gameEngine->checkCommandValidity(commandString);
			//save the effect 
			currentCommand->saveEffect("Valid Command: Updating the state "+ pastState+" to the state "+ gameEngine->currentState->name);
		}
		else {

		}
		//outputing the saved command and its effect
		std::cout << std::endl << "The given command has been saved with the following information" << std::endl;
		std::cout << "Name ->" << currentCommand->name << std::endl;
		std::cout << "Effect ->" << currentCommand->effect << std::endl<< std::endl;

		std::cout << "Type \"yes\" to continue testing :" << std::endl;
		std::getline(std::cin, continueTesting);

	} while (continueTesting._Equal("yes"));
	

	delete gameEngine;
	gameEngine = NULL;
	
}
