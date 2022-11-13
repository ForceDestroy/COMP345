#include "LoggingObserver.h"

#include "../CommandProcessing/CommandProcessing.h"
#include "../Orders/Orders.h"

inline void testLoggingObserver()
{
	LogObserver* logObserver = new LogObserver();

	// Test Command::saveEffect
	Command* command = new Command("loadmap", "");
	command->Attach(logObserver);
	command->saveEffect("Command loadmap is valid for the current state");

	// Test CommandProcessor::saveCommand
	CommandProcessor* commandProcessor = new CommandProcessor();
	commandProcessor->Attach(logObserver);
	commandProcessor->saveCommand(command);

	// Test Order::execute()
	/*
	deployOrder* order = new deployOrder();
	order->Attach(logObserver);
	order->execute();
	*/

	// Test OrderList::addOrder()
	/*
	OrdersList* ordersList = new OrdersList();
	ordersList->Attach(logObserver);
	ordersList->add(order);
	*/

	// Test GameEngine::transition()
	/*
	GameEngine* gameEngine = new GameEngine();
	gameEngine->Attach(logObserver);
	
	Transition transition = new Transition()
	transition->Attach(logObserver)
	transition->transitionState(gameEngine, 0, "loadmap");
	*/

	// Cleanup
	command->Detach(logObserver);
	commandProcessor->Detach(logObserver);

	delete logObserver;
	delete commandProcessor;

	logObserver = NULL;
	commandProcessor = NULL;
}