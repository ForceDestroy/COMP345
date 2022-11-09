#include "CommandProcessing.h"
#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif
#define ever (;;)


void testCommandProcessor(std::vector<Command*> validCommands)
{
	CommandProcessor* cmdProcessor = new CommandProcessor();
	FileLineReader* flr = new FileLineReader("Commands.txt");
	FileCommandProcessorAdapter* fcpa = new FileCommandProcessorAdapter(flr);
	//for ever{
		/*cmdProcessor->getCommand(validCommands, "cmd");
		std::cout << "The command list: "<< *cmdProcessor << std::endl;*/

		fcpa->getCommand(validCommands, "file");
		std::cout << "The command list aloha: " << *cmdProcessor << std::endl;

	//}
	delete flr;
	delete fcpa;
	delete cmdProcessor;
}
