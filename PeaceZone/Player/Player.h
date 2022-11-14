#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>

#include "../Map/Map.h"
#include "../Orders/Orders.fwd.h"
#include "../Cards/Cards.h"

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

//Player class
class Player
{
private:
    //variables for the player
    std::vector<Territory*>* territories;
    OrdersList* listOfOrders;
    //variables for IssueOrderPhase
    bool hasPlayedCard;
    bool hasDefended;
    bool hasAttacked;
    std::vector<Territory*>* committedTerritories;
    std::vector<Territory*>* attackedTerritories;
public:
    //variable for the player
    Hand* handOfCards;
    std::string name;
    int reinforcementPool;
    //variable for IssueOrderPhase
    bool hasFinishedIssuingOrders;
    //checks if player has conquered at least 1 territory this turn
    bool hasConqTerritory;
    std::vector<Player*>* negotiateList;

    //Constructor
    Player();
    Player(std::string name);
    Player(std::vector<Territory*>* territories, Hand* handOfCards, OrdersList* listOfOrders);
    //Copy constructor
    Player(const Player& player);
    //Destructor
    ~Player();
    //Player methods
    std::vector<Territory*> toAttack();
    std::vector<Territory*> toDefend();
    void issueOrder();
    bool hasLost();
    void resetIssueOrderPhase();
    std::vector<Territory*>* getTerritories();
    OrdersList* getOrdersList();
    bool truce(Player* player);
    void removeTerritory(Territory* t);

    //Add players
    void addPlayerTerritories(Territory* territorie);

    // Setters
    void setPlayerHandOfCards(Hand* handOfCards);

    void setPlayerListOfOrders(OrdersList* listOfOrders);

    void setReinforcementPool(int reinforcementPool);

    void addNegotiateList(Player* player);

    //Getter
    Hand* getPlayerHandOfCards();

    //Overloaded operators
    Player& operator=(const Player& p);
    friend std::ostream& operator<<(std::ostream& out, const Player& p);
};