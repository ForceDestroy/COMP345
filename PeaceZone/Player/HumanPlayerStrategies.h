#pragma once
#include "PlayerStrategy.h"
#include "Player.h"
#include "../Cards/Cards.h"
#include "../GameEnginer/GameEngine.h"
class HumanPlayerStrategy : public PlayerStrategy {
public:
	// terToAttack and terToDefend stores an appropriate territory every time an order is issued
	std::vector<Territory*> terToAttack;
	std::vector<Territory*> terToDefend;
	// Constructors
	HumanPlayerStrategy();
	HumanPlayerStrategy(HumanPlayerStrategy* hps);
	// Destructors
	~HumanPlayerStrategy();
	// Get territory by name
	Territory* getTerByName(Player* player, std::string name);
	// Get name of an owned territory
	std::string getName(Player* player);
	// Get number of troops
	int getTroops(Player* player, int troopLim);
	// Get the action of the player
	char getOption();
	// toAttack and toDefend are only decided after a player has finish issuing order since orders are manually input
	std::vector<Territory*> toAttack(Player* player) override;
	std::vector<Territory*> toDefend(Player* player) override;
	void issueOrder(Player* player, GameEngine* ge);
};