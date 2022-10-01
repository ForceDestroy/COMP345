#pragma once
#include <vector>
#include <string>
#include <iostream>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

class Territory;
class Cards;
class Orders;

class Player
{
    private:
    std::vector<Territory*>* territories;
    std::vector<Cards*>* handOfCards;
    std::vector<Orders*>* orders;
    public:
        Player();
        ~Player();
        Player(const Player& player);
        Player& operator=(const Player& p);
        void toAttack();
        void toDefend();
        void issueOrder();
};