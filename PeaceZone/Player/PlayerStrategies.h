#pragma once
#include "Player.h"
class GameEngine;
class PlayerStrategy {
public:
	std::string type;
	virtual std::vector<Territory*> toAttack(Player* player) = 0;
	virtual std::vector<Territory*> toDefend(Player* player) = 0;
	virtual void issueOrder(Player* player) = 0;
	virtual void resetIssueOrderPhase() = 0;
	virtual std::string describe() = 0 ;

	friend std::ostream& operator<<(std::ostream& out, const PlayerStrategy& p);
};

class AggressivePlayerStrategy : public PlayerStrategy{
public:
	int committedTroups;
	//Constructors
	AggressivePlayerStrategy();
	AggressivePlayerStrategy(const AggressivePlayerStrategy &a);
	~AggressivePlayerStrategy();

	// Methods
	std::vector<Territory*> toAttack(Player* player);
	std::vector<Territory*> toDefend(Player* player);
	void issueOrder(Player* player);
	void resetIssueOrderPhase();
	std::string describe();
	AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& a);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	//Constructors
	BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy &b);
	~BenevolentPlayerStrategy();

	// Methods
	std::vector<Territory*> toAttack(Player* player);
	std::vector<Territory*> toDefend(Player* player);
	void issueOrder(Player* player);
	void resetIssueOrderPhase();
	std::string describe() ;
	BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& b);
};


class NeutralPlayerStrategy : public PlayerStrategy {
public:
	//Constructors
	NeutralPlayerStrategy();
	NeutralPlayerStrategy(const NeutralPlayerStrategy &n);
	~NeutralPlayerStrategy();

	// Methods
	std::vector<Territory*> toAttack(Player* player);
	std::vector<Territory*> toDefend(Player* player);
	void issueOrder(Player* player);
	void resetIssueOrderPhase();
	std::string describe();
	NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& n);
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
	bool hasCheated;
	//Constructors
	CheaterPlayerStrategy();
	CheaterPlayerStrategy(const CheaterPlayerStrategy &c);
	~CheaterPlayerStrategy();

	// Methods
	std::vector<Territory*> toAttack(Player* player);
	std::vector<Territory*> toDefend(Player* player);
	void issueOrder(Player* player);
	void resetIssueOrderPhase();
	std::string describe();
	CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy& c);
};

class HumanPlayerStrategy : public PlayerStrategy {
private:
	// Get territory by name
	static Territory* getTerByName(Player* player, std::string name);
	// Get name of an owned territory
	static std::string getName(Player* player);
	// Get number of troops
	static int getTroops(Player* player, int troopLim);
	// Get the action of the player
	static char getOption();
	static std::vector<Player*> getNearbyPlayers(Player* player);
public:
	// terToAttack and terToDefend stores an appropriate territory every time an order is issued
	std::vector<Territory*> terToAttack;
	std::vector<Territory*> terToDefend;
	// Constructors
	HumanPlayerStrategy();
	HumanPlayerStrategy(HumanPlayerStrategy* hps);
	// Destructors
	~HumanPlayerStrategy();
	// toAttack and toDefend are only decided after a player has finish issuing order since orders are manually input
	std::vector<Territory*> toAttack(Player* player) override;
	std::vector<Territory*> toDefend(Player* player) override;
	void resetIssueOrderPhase() override;
	std::string describe() override;
	void issueOrder(Player* player) override;
	HumanPlayerStrategy& operator=(const HumanPlayerStrategy hps);
};