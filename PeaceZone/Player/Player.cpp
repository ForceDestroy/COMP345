#include "Player.h"

//Default constructor
Player::Player()
{
    territories = new std::vector<Territory*>();
    handOfCards = new Hand();
    listOfOrders = new OrdersList();
}

//Parameterized constructor
Player::Player(std::vector<Territory*>* territories, Hand* handOfCards, OrdersList* listOfOrders)
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

//Copy constructor
Player::Player(const Player& player)
{
    territories = new std::vector<Territory*>();
    handOfCards = player.handOfCards;
    listOfOrders = player.listOfOrders;

    for (int i = 0; i < player.territories->size(); i++)
    {
        territories->push_back(player.territories->at(i));
    }
}

//Attack method
void Player::toAttack()
{
    std::cout << "Player is attacking" << std::endl;
    for (int i = 0; i < territories->size(); i++)
    {
        std::cout << territories->at(i)->getName() << std::endl;
    }
    // get adjacent enemy territories
}
//Defend method
void Player::toDefend()
{
    std::cout << "Player is defending" << std::endl;
    for (int i = 0; i < territories->size(); i++)
    {
        std::cout << territories->at(i)->getName() << std::endl;
    }
    // get adjacent friendly territories
}
//Issue order method
void Player::issueOrder(Order* order)
{
    std::cout << "Player is issuing an order" << std::endl;
    listOfOrders->add(order);
}

//operator assignment
Player& Player::operator=(const Player& p)
{
    if (this != &p)
    {
        this->territories = p.territories;
        this->handOfCards = p.handOfCards;
        this->listOfOrders = p.listOfOrders;
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
    }
    // os << "Player's hand of cards: " << *p.handOfCards << std::endl;
    // os << "Player's list of orders: " << *p.listOfOrders <<std::endl;
    return os;
}