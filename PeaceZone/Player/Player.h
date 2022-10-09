#pragma once
#include <vector>
#include <string>
#include <iostream>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

//TODO Add comments to explain the class
//TODO change these to include headers later
class Territory;
class Hand;
class OrdersList;
class Order;

//Player class
class Player
{
private:
    std::vector<Territory*>* territories;
    Hand* handOfCards;
    OrdersList* listOfOrders;
public:
    Player();
    Player(std::vector<Territory*>* territories, Hand* handOfCards, OrdersList* listOfOrders);
    Player(const Player& player);
    ~Player();
    Player& operator=(const Player& p);
    void toAttack();
    void toDefend();
    void issueOrder( Order* order );
    
    friend std::ostream& operator<<(std::ostream& out, const Player& p);
};