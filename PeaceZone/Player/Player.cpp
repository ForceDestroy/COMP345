#include "Player.h"

Player::Player()
{
    territories = new std::vector<Territory*>();
    handOfCards = new std::vector<Cards*>();
    orders = new std::vector<Orders*>();
}

Player::~Player()
{
    delete territories;
    delete handOfCards;
    delete orders;
}

//copy constructor
Player::Player(const Player& player)
{
    territories = new std::vector<Territory*>();
    handOfCards = new std::vector<Cards*>();
    orders = new std::vector<Orders*>();
    for (Territory* territory : *player.territories)
    {
        territories->push_back(territory);
    }
    for (Cards* card : *player.handOfCards)
    {
        handOfCards->push_back(card);
    }
    for (Orders* order : *player.orders)
    {
        orders->push_back(order);
    }
}

void Player::toAttack()
{
    std::cout << "Player is attacking" << std::endl;
    // get adjacent enemy territories
}

void Player::toDefend()
{
    std::cout << "Player is defending" << std::endl;
    // get adjacent friendly territories
}

void Player::issueOrder()
{
    std::cout << "Player is issuing order" << std::endl;
}

//operator assignment
Player& Player::operator=(const Player& p)
{
    if (this != &p)
    {
        territories = p.territories;
        handOfCards = p.handOfCards;
        orders = p.orders;
    }
    return *this;
}