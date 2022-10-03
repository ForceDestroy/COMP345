#include "Player.h"

//Default constructor
Player::Player()
{
    territories = new std::vector<Territory*>();
    handOfCards = new std::vector<Cards*>();
    listOfOrders = new std::vector<Orders*>();
}

//Parameterized constructor
Player::Player(std::vector<Territory*>* territories, std::vector<Cards*>* handOfCards, std::vector<Orders*>* listOfOrders)
{
    this->territories = territories;
    this->handOfCards = handOfCards;
    this->listOfOrders = listOfOrders;
}

//Destructor
Player::~Player()
{
    delete territories;
    delete handOfCards;
    delete listOfOrders;
}

//copy constructor
Player::Player(const Player& player)
{
    territories = new std::vector<Territory*>();
    handOfCards = new std::vector<Cards*>();
    listOfOrders = new std::vector<Orders*>();
    //Copying the values into the new object
    for (Territory* territory : *player.territories)
    {
        territories->push_back(territory);
    }
    for (Cards* card : *player.handOfCards)
    {
        handOfCards->push_back(card);
    }
    for (Orders* order : *player.listOfOrders)
    {
        listOfOrders->push_back(order);
    }
}

//Attack method
void Player::toAttack()
{
    std::cout << "Player is attacking" << std::endl;
    // get adjacent enemy territories
}
//Defend method
void Player::toDefend()
{
    std::cout << "Player is defending" << std::endl;
    // get adjacent friendly territories
}
//Issue order method
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
        listOfOrders = p.listOfOrders;
    }
    return *this;
}

//osstream operator
std::ostream& operator<<(std::ostream& os, const Player& p)
{
    os << "Player's territories: " << std::endl;
    for (Territory* territory : *p.territories)
    {
        //os << *territory << std::endl;
        // Waiting on Territories << overload
    }
    os << "Player's cards: " << std::endl;
    for (Cards* card : *p.handOfCards)
    {
        //os << *card << std::endl;
        // Waiting on Card << overload
    }
    os << "Player's listOfOrders: " << std::endl;
    for (Orders* order : *p.listOfOrders)
    {
        //os << *order << std::endl;
        // Waiting on Orders << overload
    }
    return os;
}