#include "CommandProcessing.h"
#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif
#define ever (;;)


void testCommandProcessor(CommandProcessor* cmdProcessor)
{
	std::string path ("C:/ProjectSchool/COMP 345/COMP345/PeaceZone/CommandProcessing/CommandProcessorCommands.txt");

	FileLineReader* flr = new FileLineReader(path);
	FileCommandProcessorAdapter* fcpa = new FileCommandProcessorAdapter(cmdProcessor->commandList, cmdProcessor->validCommands, flr);

	std::cout << "Would you like to test command processor through command input or a file? Type \"input\" or \"file\"" << std::endl;
	
	std::string input;

	do {
		std::getline(std::cin, input);

	} while (!input._Equal("input") && !input._Equal("file"));
	
	if (input._Equal("input")) {
		cmdProcessor->getCommand();
		std::cout << "The command list from command processor: " << *cmdProcessor << std::endl<<std::endl;

	}

	if (input._Equal("file")) {
		fcpa->getCommand();
		std::cout << "The command list from file command processor adapter: " << *fcpa << std::endl << std::endl;

	}


	flr->fileStream.close();
	
	delete flr;
	delete fcpa;
	delete cmdProcessor;
}
