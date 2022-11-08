#include "CommandProcessing.h"
#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

void testCommandProcessor(GameEngine* gameEngine)
{
	CommandProcessor* cmdProcessor = new CommandProcessor();
	cmdProcessor->getCommand(gameEngine);
	std::cout << "The command list: "<< *cmdProcessor << std::endl;

	delete cmdProcessor;
}
