#pragma once
#include "Player.h"
class PlayerStrategy {
public:
		virtual std::vector<Territory*> toAttack(Player* player) = 0;
		virtual std::vector<Territory*> toDefend(Player* player) = 0;
		virtual void issueOrder(Player* player) = 0;
		virtual void resetIssueOrderPhase() = 0;
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
	AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& a);
	friend std::ostream& operator<<(std::ostream& out, const AggressivePlayerStrategy& a);
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
	BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& b);
	friend std::ostream& operator<<(std::ostream& out, const BenevolentPlayerStrategy& b);
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
	NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& n);
	friend std::ostream& operator<<(std::ostream& out, const NeutralPlayerStrategy& n);
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
	CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy& c);
	friend std::ostream& operator<<(std::ostream& out, const CheaterPlayerStrategy& c);
};