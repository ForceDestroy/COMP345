#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "../Map/Map.h"

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

//TODO Add comments to explain the class
//TODO change these to include headers later

class Hand;
class OrdersList;
class Order;

//Player class
class Player
{
private:
    //variables for the player
    std::vector<Territory*>* territories;
    Hand* handOfCards;
    OrdersList* listOfOrders;
public:
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
    
    //Overloaded operators
    Player& operator=(const Player& p);
    friend std::ostream& operator<<(std::ostream& out, const Player& p);
};