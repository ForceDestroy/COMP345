#pragma once
#include "Player.h"
class PlayerStrategy {
public:
		virtual std::vector<Territory*> toAttack(Player* player) = 0;
		virtual std::vector<Territory*> toDefend(Player* player) = 0;
		virtual void issueOrder(Player* player) = 0;
};