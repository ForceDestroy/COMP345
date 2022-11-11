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
	std::string path ("C:/Users/Mimi/Documents/GitHub/COMP345/PeaceZone/CommandProcessing/Commands.txt");

	FileLineReader* flr = new FileLineReader(path);
	FileCommandProcessorAdapter* fcpa = new FileCommandProcessorAdapter(cmdProcessor->commandList, cmdProcessor->validCommands, flr);
	//for ever{
		//cmdProcessor->getCommand();
		//std::cout << "The command list from command processor: "<< *cmdProcessor << std::endl;

		fcpa->getCommand();
		std::cout << "The command list from file command processor adapter: " << *fcpa << std::endl<<std::endl;

		fcpa->getCommand();
		std::cout << "The command list from file command processor adapter: " << *fcpa << std::endl << std::endl;

		flr->fileStream.close();
	//}
	delete flr;
	delete fcpa;
	delete cmdProcessor;
}
