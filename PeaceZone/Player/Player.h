#pragma once
#include <vector>
#include <string>
#include <iostream>

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
public:
    //variables for the player
    int reinforcementPool;

    //Constructor
    Player();
    Player(std::vector<Territory*>* territories, Hand* handOfCards, OrdersList* listOfOrders);
    //Copy constructor
    Player(const Player& player);
    //Destructor
    ~Player();
    //Player methods
    void toAttack();
    void toDefend();
    void issueOrder(std::string order);
    bool hasLost();
    std::vector<Territory*>* getTerritories();
    OrdersList* getOrdersList();

    //Overloaded operators
    Player& operator=(const Player& p);
    friend std::ostream& operator<<(std::ostream& out, const Player& p);
};