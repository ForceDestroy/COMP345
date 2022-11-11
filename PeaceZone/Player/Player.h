#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>

#include "../Map/Map.h"
#include "../Orders/Orders.h"
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
    Hand* handOfCards;
    OrdersList* listOfOrders;
    std::string name;
    //variables for IssueOrderPhase
    bool hasPlayedCard;
    bool hasDefended;
    bool hasAttacked;
    std::vector<Territory*> *committedTerritories;
public:
    //variable for the player
    int reinforcementPool;
    //variable for IssueOrderPhase
    bool hasFinishedIssuingOrders;

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
    
    //Add players
    void addPlayerTerritories(Territory* territorie);
    
    // Setters
    void setPlayerHandOfCards(Hand* handOfCards);

    void setPlayerListOfOrders(OrdersList* listOfOrders); 

    void setReinforcementPool(int reinforcementPool);

    //Overloaded operators
    Player& operator=(const Player& p);
    friend std::ostream& operator<<(std::ostream& out, const Player& p);
};