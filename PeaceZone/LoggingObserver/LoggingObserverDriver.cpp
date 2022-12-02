#include "LoggingObserver.h"

#include "../CommandProcessing/CommandProcessing.h"
#include "../Orders/Orders.h"

inline void testLoggingObserver()
{
	// Empty the log file
	std::string LogFile = "C:\\COMP345\\PeaceZone\\LoggingObserver\\gamelog.txt";
	std::ofstream output;

	// Open LogFile and Get LogString
	output.open(LogFile, std::ios_base::trunc);

	// Write LogString to the LogFile
	output << "" << std::endl;

	// CLose the LogFile
	output.close();

	LogObserver* logObserver = new LogObserver();

	// Test Command::saveEffect
	Command* command = new Command("loadmap", "");
	command->Attach(logObserver);
	command->saveEffect("Command loadmap is valid for the current state");

	// Test CommandProcessor::saveCommand
	CommandProcessor* commandProcessor = new CommandProcessor();
	commandProcessor->Attach(logObserver);
	commandProcessor->getCommand("loadmap");

	// Test Order::execute()
	Player* p = new Player("p1");
	Territory* t = new Territory(0, "Test", 0);
	t->owner = p;


	deployOrder* order = new deployOrder(p, t, 1);
	order->Attach(logObserver);
	order->execute();

	// Test OrderList::addOrder()
	OrdersList* ordersList = new OrdersList();
	ordersList->Attach(logObserver);
	ordersList->add(order);

	// Test GameEngine::transition()
	GameEngine* gameEngine = new GameEngine();
	gameEngine->Attach(logObserver);
	gameEngine->checkCommandValidity("loadmap");
	
	// Cleanup
	command->Detach(logObserver);
	commandProcessor->Detach(logObserver);
	order->Detach(logObserver);
	ordersList->Detach(logObserver);
	gameEngine->Detach(logObserver);

	delete logObserver;
	delete commandProcessor;
	delete ordersList;
	delete t;
	delete p;
	delete gameEngine;

	logObserver = NULL;
	commandProcessor = NULL;
	order = NULL;
	ordersList = NULL;
	t = NULL;
	p = NULL;
	gameEngine = NULL;
}