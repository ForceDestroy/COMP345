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
class Cards;
class Orders;

//Player class
class Player
{
private:
    std::vector<Territory*>* territories;
    std::vector<Cards*>* handOfCards;
    std::vector<Orders*>* listOfOrders;
public:
    Player();
    Player(std::vector<Territory*>* territories, std::vector<Cards*>* handOfCards, std::vector<Orders*>* listOfOrders);
    Player(const Player& player);
    ~Player();
    Player& operator=(const Player& p);
    void toAttack();
    void toDefend();
    void issueOrder();
    
    friend std::ostream& operator<<(std::ostream& out, const Player& p);
};