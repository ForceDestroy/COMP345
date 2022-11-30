#pragma once
#include "PlayerStrategy.h"
#include "Player.h"
#include "../Cards/Cards.h"
#include "../GameEnginer/GameEngine.h"
class HumanPlayerStrategy : public PlayerStrategy {
public:
	std::vector<Territory*> terToAttack;
	std::vector<Territory*> terToDefend;
	HumanPlayerStrategy();
	HumanPlayerStrategy(HumanPlayerStrategy* hps);
	~HumanPlayerStrategy();
	char getOption();
	std::string getName(Player* player);
	bool isAPlayer(GameEngine* ge, std::string name);
	int getTroops(Player* player, int troopLim);
	std::vector<Territory*> toAttack(Player* player) override;
	std::vector<Territory*> toDefend(Player* player) override;
	void issueOrder(Player* player, GameEngine* ge);
	Territory* getTerByName(Player* player, std::string name);
};