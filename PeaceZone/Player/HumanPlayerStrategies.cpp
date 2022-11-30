#include "HumanPlayerStrategies.h"
#include "PlayerStrategy.h"
#include "Player.h"
#include "../Cards/Cards.h"
#include "../GameEnginer/GameEngine.h"


#pragma region HumanPlayerStrategies
HumanPlayerStrategy::HumanPlayerStrategy()
{
	terToAttack = new std::vector<Territory*>();
	terToDefend = new std::vector<Territory*>();
}
HumanPlayerStrategy::HumanPlayerStrategy(HumanPlayerStrategy* hps)
{
	this->terToAttack = hps->terToAttack;
	this->terToDefend = hps->terToDefend;
}
HumanPlayerStrategy::~HumanPlayerStrategy()
{
	delete terToAttack;
	delete terToDefend;
}
std::vector<Territory*> HumanPlayerStrategy::toAttack(Player* p)
{
	return terToAttack;
}
std::vector<Territory*> HumanPlayerStrategy::toDefend(Player* p)
{
	return terToDefend;
}
bool HumanPlayerStrategy::isAPlayer(Game)
Territory* HumanPlayerStrategy::getTerByName(Player* p, std::string name)
{
	for (Territory* t : p->territories)
	{
		if (t->name = name)
			return t;
	}
	return NULL;
}
std::string HumanPlayerStrategy::getName(Player* p)
{
	std::string terName;
	bool nameFound = false;
	std::cout << "Enter a territory name(\"back\" to go back): " << std::endl;
	while (!nameFound)
	{
		std::cin << terName;
		if (terName == "back")
			return terName;
		for (std::string n : p->territories->name)
		{
			if (terName == n)
			{
				return terName;
			}
		}
		std::cout << "Territory name not found. Try again (\"back\" to go back): " << std::endl;
	}
}
int HumanPlayerStrategy::getTroops(Player* p, int troopLim)
{
	int troops
	std::cout << "Enter number of troops to deploy (0 to go back): " << std::endl;
	std::cin << troops;
	while (troops < 0 || troops > troopLim)
	{
		std::cout << "Invalid troop number. Try again (0 to go back): " << std::endl;
		std::cin << troops;
	}
	return troops;
}
char HumanPlayerStrategy::getOption()
{
	char option;
	std::cout << "Please enter your option ('a' to attack, 'd' to defend, 's' to skip, 'c' to play a card" << std::endl;
	std::cin << option;
	while (option != 'a' || option != 'd' || option != 's' || option != 'c')
	{
		std::cout << "Invalid option, please try again." << std::endl;
		std::cout << "Please enter your option ('a' to attack, 'd' to defend, 's' to skip, 'c' to play a card" << std::endl;
		std::cin << option;
	}

	return option;
}
void HumanPlayerStrategy::issueOrder(Player* p, GameEngine* ge)
{
	std::cout "Issue order phase start." << std::endl;
	std::cout "Deploy phase." << std::endl;
	terToAttack.clear();
	terToDefend.clear();
	std::string name;
	int troops;
	while (p->reinforcementPool > 0)
	{
		std::cout << "Enter territory to reinforce." << std::endl;
		name = getName(p);
		troops = getTroops(p, p->reinforcementPool);
		while (troops == 0 || name == "back")
		{
			name = getName(p);
			troops = getTroops(p, p->reinforcementPool);
		}
		p->listOfOrders->add(new deployOrder(p, getTerByName(p, name), troops);
		p->reinforcementPool -= troops;
		terToDefend.push_back(getTerByName(p, name));
		std::cout << "Order added." << std::endl;
	}
	std::cout << "Deploy phase end." << std::endl;
	std::cout << "Attack and defend phase start." << std::endl;
	bool done = false;
	Territory* source = NULL, target = NULL;
	bool nameValid = false; bool validSourceAndTarget = false;
	while (!done)
	{
		switch (getOption())
		{
		case 'c':
		{
			if (p->handOfCards->listOfCards->size() == 0)
				std::cout << "You do not have any cards." << std::endl;
			else if (p->hasPlayedCard)
				std::cout << "Player can not player more than 1 card per turn." << std::endl;
			else
			{
				std::cout << "Player's current hand of card: " << std::endl;
				std::cout << *p->handOfCards << std::endl;
				std::cout << "Please choose a card number to play, from 1 to " << p->handOfCards->listOfCards->size() << std::endl;
				std::cout << "Type 0 to go back." << std::endl;
				int cardNum = 0;
				std::cin << cardNum;
				while (cardNum > p->handOfCards->listOfCards->size() || cardNum < 0)
				{
					if (cardNum == 0)
						goto finish;
					std::cout << "Wrong number, please try again: ";
					std::cin << cardNum;
				}
				Card* toPlay = p->handOfCards->listOfCards->at(cardNum - 1);
				switch (toPlay)
				{
				case bomb:
				{ 
					std::cout << "Enter bomb target territory name (\"back\" to go back): " << std::endl;
					std::cin << name;
					nameValid = false;
					while (!nameValid)
					{
						if (name == "back")
							goto finish;
						for (auto t : p->territories)
						{
							for (auto n : p->territories->neighbors)
							{
								if (name == n->name && getTerByName(p, name)->owner != p)
									nameValid = true;
							}
						}
						if (!nameValid)
							std::cout << "Not valid territory, try again." << std::endl;
						std::cin << name;
					}
					p->listOfOrders->add(new bombOrder(this, getTerByName(p, name)));
					terToAttack.push_back(getTerByName(p, name));
					std::cout << "Order added." << std::endl;
				}
				case blockade:
				{
					std::cout << "Enter blockade target territory name (\"back\" to go back): " << std::endl;
					name = getName(p);
					nameValid = false;
					while (!nameValid)
					{
						if (name == "back")
							goto finish;
						for (auto t : p->territories)
						{
							for (auto n : p->territories->neighbors)
							{
								if (name == n->name)
									nameValid = true;
							}
						}
						if (!nameValid)
							std::cout << "Not valid territory, try again." << std::endl;
						name = getName(p);
					}
					p->listOfOrders->add(new blockadeOrder(this, getTerByName(p, name)));
					terToDefend.push_back(getTerByName(p, name));
					std::cout << "Order added." << std::endl;
				}
				case airlift:
				{
					std::cout << "Enter airlift target territory name (\"back\" to go back): " << std::endl;
					bool validSandT = false;
					name = "";
					while (!validSandT)
					{
						name = getName(p);
						if (name == "back")
							goto finish;
						source = getTerByName(p, name);
						name = getName(p);
						if (name != "back")
						{
							target = getTerByName(p, name);
							if (source == target)
							{
								std::cout << "Invalid input, try again. " << std::endl;
							}
							else
								validSandT = true;
						}
						troops = getTroops(p, source
					}
					p->listOfOrders->add(new airliftOrder(this, source, target, troops);
					terToDefend.push_back(getTerByName(p, name));
					std::cout << "Order added." << std::endl;
				}
				case diplomacy:
				{
					nameValid = false;
					validSourceAndTarget = false;
					source = NULL;
					target = NULL;
					while (!nameValid)
					{
						//Receives name of source and target of attack and checks them
						while (!validSourceAndTarget)
						{
							name = "";
							std::cout << "Select territory to transfer troops from:";
							// Get name of source territory
							name = getName(p);
							// Checks if player wants to go back to order choosing
							if (name == "back")
								goto:finish;
							source = getTerByName(p, name);
							// Get name of target
							std::cout << "Select territory to transfer troops to: ";
							name = getName(p);
							target = getTerByName(p, name);
							// If the player wants to go back, program returns to choosing source territory
							if (name != "back")
							{
								if (source == p && target == p)
									validSourceAndTarget = true;
								else
								{
									std::cout << "Invalid inputs, please try again" << std::endl;
								}
							}
						}
						// Choose number of troops used in attack
						troops = getTroops(p, source->armyCount - 1);
						if (troops != 0)
							nameValid = true;
					}
					p->listOfOrders->add(new airliftOrder(p, source, target, troops));
					terToDefend.push_back(source);
					std::cout << "Order added." << std::endl;
				}
				case reinforcement:
				{
					//Add more reinforcements to the player
					break;
				}
				default:
					break;
				}
				p->hasPlayedCard = true;
			}
		}
		case 's':
		{
			std::cout << "Issue order phase finish." << std::endl;
			done = true;
		}
		case 'a':
		{
			std::cout << "Issue attack order." << std::endl;
			nameValid = false;
			validSourceAndTarget = false;
			source = NULL;
			target = NULL;
			while (!nameValid)
			{
				//Receives name of source and target of attack and checks them
				while (!validSourceAndTarget)
				{
					name = "";
					std::cout << "Select territory to attack from:";
					// Get name of source territory
					name = getName(p);
					// Checks if player wants to go back to order choosing
					if (name == "back")
						goto:finish;
					source = getTerByName(p, name);
					// Get name of target
					std::cout << "Select territory to attack: ";
					name = getName(p);
					target = getTerByName(p, name);
					// If the player wants to go back, program returns to choosing source territory
					if (name != "back")
					{
						if (source == p && target == NULL)
							for (auto t : source->neighbors)
							{
								if (t->name == name)
									validSourceAndTarget = true;
							}
						else
						{
							std::cout << "Invalid inputs, please try again" << std::endl;
						}
					}
				}
				// Choose number of troops used in attack
				troops = getTroops(p, source->armyCount - 1);
				if (troops != 0)
					nameValid = true;
			}
			p->listOfOrders->add(new advanceOrder(p, source, target, troops));
			terToAttack.push_back(source);
			std::cout << "Order added." << std::endl;
		}
		case 'd':
		{
			std::cout << "Issue defend order." << std::endl;
			nameValid = false;
			validSourceAndTarget = false;
			source = NULL;
			target = NULL;
			while (!nameValid)
			{
				//Receives name of source and target of attack and checks them
				while (!validSourceAndTarget)
				{
					name = "";
					std::cout << "Select territory to transfer troops from:";
					// Get name of source territory
					name = getName(p);
					// Checks if player wants to go back to order choosing
					if (name == "back")
						goto:finish;
					source = getTerByName(p, name);
					// Get name of target
					std::cout << "Select territory to transfer troops to: ";
					name = getName(p);
					target = getTerByName(p, name);
					// If the player wants to go back, program returns to choosing source territory
					if (name != "back")
					{
						if (source == p && target == p)
						{	
							//neighbors check
							for (auto t : source->neighbors)
							{
								if (t == target)
									validSourceAndTarget = true;
							}
						}
						else
						{
							std::cout << "Invalid inputs, please try again" << std::endl;
						}
					}
				}
				// Choose number of troops used in attack
				troops = getTroops(p, source->armyCount - 1);
				if (troops != 0)
					nameValid = true;
			}
			p->listOfOrders->add(new advanceOrder(p, source, target, troops));
			terToDefend.push_back(source);
			std::cout << "Order added." << std::endl;
		}
		default :
		{
			std::cout << "Something went wrong, literally impossible to get here" << std::endl;
		}
		}
		finish;
	}
}
#pragma endregion