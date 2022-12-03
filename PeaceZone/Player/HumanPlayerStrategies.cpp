#include "HumanPlayerStrategies.h"
#include "PlayerStrategies.h"
#include "Player.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"


#pragma region HumanPlayerStrategies
// Default constructor
HumanPlayerStrategy::HumanPlayerStrategy()
{
}

// Copy constructor
HumanPlayerStrategy::HumanPlayerStrategy(HumanPlayerStrategy* hps)
{
	this->terToAttack = hps->terToAttack;
	this->terToDefend = hps->terToDefend;
}

// Destructor
HumanPlayerStrategy::~HumanPlayerStrategy()
{
	terToAttack.~vector();
	terToDefend.~vector();
}

// Returns territories being attacked/bombed
std::vector<Territory*> HumanPlayerStrategy::toAttack(Player* p)
{
	return terToAttack;
}

// Returns territories being deployed to, defended, blockade, airlift
std::vector<Territory*> HumanPlayerStrategy::toDefend(Player* p)
{
	return terToDefend;
}

// Takes a player and a territory name as parameters
// If the player owns the territory with that name, return the terrritory
// If not return null
Territory* HumanPlayerStrategy::getTerByName(Player* p, std::string name)
{
	for (int i = 0; i < p->territories->size(); i++)
	{
		if (p->territories->at(i)->name == name)
			return p->territories->at(i);
	}
	return NULL;
}

// Receives a string input of a name of a territory that the player owns
// If the user enters a wrong name, they are asked again until they get a correct one or the choose to go back
// The user can choose to go back if they type "back"
std::string HumanPlayerStrategy::getName(Player* p)
{
	std::string terName;
	bool nameFound = false;
	std::cout << "Enter a territory name(\"back\" to go back): " << std::endl;
	while (!nameFound)
	{
		std::cin >> terName;
		if (terName == "back")
			return terName;
		for (int i = 0; i < p->territories->size(); i ++)
		{
			if (terName == p->territories->at(i)->name)
			{
				return terName;
			}
		}
		std::cout << "Territory name not found. Try again (\"back\" to go back): " << std::endl;
	}
}

// Receives an input from the user that is the number of troops to be used in an order
// Input must be non-negative and less than a limit amount (May be amount of reserve units or current troops on a territory)
// Input is looped until a correct number is entered
// User may go back by typing 0
int HumanPlayerStrategy::getTroops(Player* p, int troopLim)
{
	int troops = 0;
	std::cout << "Enter number of troops to deploy (0 to go back): " << std::endl;
	std::cin >> troops;
	while (troops < 0 || troops > troopLim)
	{
		std::cout << "Invalid troop number. Try again (0 to go back): " << std::endl;
		std::cin >> troops;
	}
	return troops;
}

// This function makes the user choose an action after the deploy phase
// Type 'a' to attack
// Type 'd' to defend
// Type 'c' to play a card
// Type 's' to skip. This will end a player's issue order phase
// This will looop until the player chooses a valid option
char HumanPlayerStrategy::getOption()
{
	char option = ' ';
	std::cout << "Please enter your option: 'a' to attack, 'd' to defend, 'c' to play a card, 's' to skip" << std::endl;
	std::cin >> option;
	while (option != 'a' || option != 'd' || option != 's' || option != 'c')
	{
		std::cout << "Invalid option, please try again." << std::endl;
		std::cout << "Please enter your option 'a' to attack, 'd' to defend, 'c' to play a card, 's' to skip" << std::endl;
		std::cin >> option;
	}
	return option;
}

// This is the main funciton of the class
// This function starts by beginning the deploy phase
// Then it will go to ask players for their actions until the user decides to finish
void HumanPlayerStrategy::issueOrder(Player* p, GameEngine* ge)
{
	std::cout << "Issue order phase start." << std::endl;
	std::cout << "Deploy phase." << std::endl;
	terToAttack.clear();
	terToDefend.clear();
	std::string name;
	int troops;
	// Start of deploy orders
	// Looped until their are no more reserve troops
	while (p->reinforcementPool > 0)
	{
		std::cout << "Enter territory to reinforce." << std::endl;
		// Get the name of an owned territory
		name = getName(p);
		// Select the number of troops to send
		troops = getTroops(p, p->reinforcementPool);
		// If the player enters "back" for the name or "0" for troops, the program will go back to asking for the name
		while (troops == 0 || name == "back")
		{
			name = getName(p);
			troops = getTroops(p, p->reinforcementPool);
		}
		// Adds a deploy order of "troops" troops to the territory with "name" name
		p->listOfOrders->add(new deployOrder(p, getTerByName(p, name), troops));
		p->reinforcementPool -= troops;
		terToDefend.push_back(getTerByName(p, name));
		std::cout << "Order added." << std::endl;
	}

	std::cout << "Deploy phase end." << std::endl;
	std::cout << "Attack and defend phase start." << std::endl;
	// bool done is used to check if players are finished with their issue order phaes
	bool done = false;
	// source and target denotes the source and target territory of an order
	Territory* source = NULL;
	Territory* target = NULL;
	bool nameValid = false, validSourceAndTarget = false;;
	while (!done)
	{
		// Different cases depending on the player action
		switch (getOption())
		{
		// Player wants to play a card
		case 'c':
		{
			// Checks if a player has a card or player has already played a card
			if (p->handOfCards->listOfCards->size() == 0)
				std::cout << "You do not have any cards." << std::endl;
			else if (p->hasPlayedCard)
				std::cout << "Player can not player more than 1 card per turn." << std::endl;
			else
			{
				// Prints the player current hand of cards
				std::cout << "Player's current hand of card: " << std::endl;
				std::cout << *p->handOfCards << std::endl;
				// Let the player choose the card to play through the index of the hand
				// Example if the player has 3 cards then the player can choose 1, 2 or 3 corresponding to the card's index in the hand + 1
				std::cout << "Please choose a card number to play, from 1 to " << p->handOfCards->listOfCards->size() << std::endl;
				std::cout << "Type 0 to go back." << std::endl;
				int cardNum = 0;
				std::cin >> cardNum;
				// Checks if the user enters a valid number (between 1 and the hand size)
				while (cardNum > p->handOfCards->listOfCards->size() || cardNum < 0)
				{
					if (cardNum == 0)
						// goto finish will make it so that the user return to getOption() to choose a different action
						goto finish;
					std::cout << "Wrong number, please try again (0 to go back): ";
					std::cin >> cardNum;
				}
				Card* toPlay = p->handOfCards->listOfCards->at(cardNum - 1);
				// Different cases depending on which card the player decides to play
				// Cases: bomb, airlift, blockade, negotiate
				switch (toPlay->Play(*p->handOfCards))
				{
				// Bomb card
				case bomb:
				{ 
					std::cout << "You've chosen to play the bomb card." << std::endl;
					std::cout << "Enter bomb target territory name (\"back\" to go back): " << std::endl;
					std::cin >> name;
					nameValid = false;
					// Looped until valid name is entered or user choose to go back
					while (!nameValid)
					{
						// Go back to getOption() if the player types "back"
						if (name == "back")
							goto finish;
						// Checks if the territory is not owned by the player and is adjacent to an owned territory
						for (int i = 0; i < p->territories->size(); i++)
						{
							for (Territory* n : p->territories->at(i)->neighbors)
							{
								if (name == n->name && getTerByName(p, name) == NULL)
								{
									target = n;
									nameValid = true;
								}
							}
						}
						if (!nameValid)
							std::cout << "Not valid territory, try again(\"back\" to go back): " << std::endl;
						std::cin >> name;
					}
					// Adds a bomb order and adds a the target territory to terToAttack
					p->listOfOrders->add(new bombOrder(p, target));
					terToAttack.push_back(getTerByName(p, name));
					std::cout << "Bomb order added." << std::endl;
				}
				// Blockade card
				case blockade:
				{
					std::cout << "You've chosen to play the blockade order." << std::endl;
					std::cout << "Enter blockade target territory name (\"back\" to go back): " << std::endl;
					// Get target territory name (must be owned by player)
					name = getName(p);
					// Add a blockade order an add target territory to terToDefend
					p->listOfOrders->add(new blockadeOrder(p, getTerByName(p, name)));
					terToDefend.push_back(getTerByName(p, name));
					std::cout << "Blockade order added." << std::endl;
				}
				//Airlift card
				case airlift:
				{
					std::cout << "You've chosen to play the airlift order." << std::endl;
					std::cout << "Enter airlift target territory name (\"back\" to go back): " << std::endl;
					// Checks if the entered source and target territory is valid
					nameValid = false;
					name = "";
					source = NULL;
					target = NULL;
					// looped until valid source and target or go back
					while (!nameValid)
					{
						std::cout << "Select target to send troops from. " << std::endl;
						name = getName(p);
						if (name == "back")
							goto finish;
						source = getTerByName(p, name);

						std::cout << "Select target to send troops to. " << std::endl;
						name = getName(p);
						if (name != "back")
						// If name == "back" then go back to selecting source target
						{
							target = getTerByName(p, name);
							if (source == target) // If the source and target territory is the same, go back to selecting source territory
							{
								std::cout << "Invalid input, try again (\"back\" go to back): " << std::endl;
							}
							else
							{
								std::cout << "Enter number of troops to send. " << std::endl;
								troops = getTroops(p, source->armyCount-1);
								if (troops != 0)
									nameValid = true; // exit loop
								// IF troops == 0, go back to selecting source territory
							}
						}
					}
					// Adds a new airlift order and adds the target territory to terToDefend
					p->listOfOrders->add(new airliftOrder(p, source, target, troops));
					terToDefend.push_back(getTerByName(p, name));
					std::cout << "Airlift order added." << std::endl;
				}
				// Negotiate card
				case diplomacy:
				{
					std::cout << "You've chosen to play the negotiate card." << std::endl;
					std::cout << "Please enter a player to negotiate with: " << std::endl;
					name = "";
					nameValid = false;
					// Looped until a valid player is acquired or going back
					while (!nameValid)
					{
						std::cin >> name;
						// Checks for the player name on the list of players and checks if the target player is not the one playing the card
						for (Player* n : ge->playerList)
						{
							if (n->name == name && p->name != name)
							{
								nameValid = true;
								p->listOfOrders->add(new negotiateOrder(p, n));
							}
						}
						if (!nameValid)
							std::cout << "Invalid name. Try again (\"back\" to go back): " << std::endl;
					}
					std::cout << "Negotiate order added." << std::endl;
				}
				// Don't know what this does / how to implement
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
		// User wants to end issue order phase
		case 's':
		{
			std::cout << "Issue order phase finish." << std::endl;
			done = true;
		}
		// User wants to attack a territory
		// This will create an advance order to a nearby enemy territory
		case 'a':
		{
			std::cout << "Issue attack order." << std::endl;
			nameValid = false;
			validSourceAndTarget = false;
			while (!validSourceAndTarget)
			{
				//Receives name of source and target of attack and checks them
				name = "";
				std::cout << "Select territory to attack from: ";
				// Get name of source territory
				name = getName(p);
				// Checks if player wants to go back to order choosing
				if (name == "back")
					goto finish;
				source = getTerByName(p, name);
				// Get name of target
				std::cout << "Select territory to attack: ";
				std::cin >> name;
				while (!nameValid) {
					// If the player wants to go back, program returns to choosing source territory
					std::cin >> name;
					if (name == "back")
						nameValid = true;
					else
					{
						// Checks if the target is a neighbor territory and is not owned by issuing player
						for (Territory* t : source->neighbors)
						{
							if (t->name == name && t->owner != p)
							{
								nameValid = true;
								target = t;
							}
						}
						if (!nameValid)
						{
							std::cout << "Invalid inputs, please try again (\"back\" to go back): " << std::endl;
						}
					}
					// If nameValid is true then choose number of troops used in attack
					if (nameValid) {
						troops = getTroops(p, source->armyCount - 1);
						if (troops != 0)
							// If number of troops is valid then exit loop
							validSourceAndTarget = true;
						else
							// If troops = 0 go back to choosing target territory
							nameValid = false;
					}
				}
			}
			// Add an advance order and add territory to terToAttack
			p->listOfOrders->add(new advanceOrder(p, source, target, troops));
			terToAttack.push_back(source);
			std::cout << "Attack (advance) order added." << std::endl;
		}
		// User wants to defend a territory
		// This will create an advance order to another owned territory
		case 'd':
		{
			std::cout << "Issue defend order." << std::endl;
			nameValid = false;
			validSourceAndTarget = false;
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
						goto finish;
					source = getTerByName(p, name);
					// Get name of target
					std::cout << "Select territory to transfer troops to: ";
					name = getName(p);
					target = getTerByName(p, name);
					// If the player wants to go back, program returns to choosing source territory
					if (name != "back")
					// if name == "back" go back to getOption()
					{
						//neighbors check
						for (Territory* t : source->neighbors)
						{
							if (t == target)
								validSourceAndTarget = true;
						}
					}
				}
				// Choose number of troops used in attack
				troops = getTroops(p, source->armyCount - 1);
				if (troops != 0)
					nameValid = true;
			}
			// Add a new advance order and add a territory to terToDefend
			p->listOfOrders->add(new advanceOrder(p, source, target, troops));
			terToDefend.push_back(source);
			std::cout << "Defend (advance) order added." << std::endl;
		}
		default :
		{
			std::cout << "Something went wrong, literally impossible to get here" << std::endl;
		}
		}
		finish:
	}
}
#pragma endregion