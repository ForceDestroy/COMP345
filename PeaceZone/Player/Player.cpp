#include "Player.h"

//Default constructor
Player::Player()
{
    name = "";
    territories = new std::vector<Territory*>();
    handOfCards = new Hand();
    listOfOrders = new OrdersList();
    reinforcementPool = 0;
}

//Parameterized constructor
Player::Player(std::string name)
{
    this->name = name;
	this->territories = new std::vector<Territory*>();
	this->handOfCards = new Hand();
	this->listOfOrders = new OrdersList();
    this->reinforcementPool = 0;
}


//Parameterized constructor
Player::Player(std::vector<Territory*>* territories, Hand* handOfCards, OrdersList* listOfOrders)
{
    this->name = "";
    this->territories = territories;
    this->handOfCards = handOfCards;
    this->listOfOrders = listOfOrders;
    this->reinforcementPool = 0;
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
    name = player.name;
    territories = new std::vector<Territory*>();
    handOfCards = player.handOfCards;
    listOfOrders = player.listOfOrders;
    reinforcementPool = player.reinforcementPool;

    for (int i = 0; i < player.territories->size(); i++)
    {
        territories->push_back(player.territories->at(i));
    }
}

//Attack method
void Player::toAttack()
{
    //getting neighbors of the territories to attack
    std::cout << "Player is now attacking" << std::endl;
    for (int i = 0; i < territories->size(); i++)
    {
        for (int j = 0; j < territories->at(i)->neighbors.size(); j++)
        {
            if (territories->at(i)->neighbors.at(j)->name != territories->at(i)->name)
            {
                std::cout << "Player is attacking " << territories->at(i)->neighbors.at(j)->name << " from " << territories->at(i)->name << std::endl;
            }
        }
    }
}
//Defend method
void Player::toDefend()
{
    //get all the territories to defend that the player owns
    std::cout << "Player is now defending" << std::endl;
    for (int i = 0; i < territories->size(); i++)
    {
        std::cout << territories->at(i)->name << std::endl;
    }
}
//Issue order method
void Player::issueOrder(std::string order)
{
    std::cout << "Player is issuing an order" << std::endl;
    Orders* o;
    //checking if the order is valid and creates the appropriate order
    if ( order == "deploy" )
    {
        o = new deployOrder();
        listOfOrders->add(o);
    }
    else if ( order == "advance" )
    {
        o = new advanceOrder();
        listOfOrders->add(o);
    }
    else if ( order == "bomb" )
    {
        o = new bombOrder();
        listOfOrders->add(o);
    }
    else if ( order == "blockade" )
    {
        o = new blockadeOrder();
        listOfOrders->add(o);
    }
    else if ( order == "airlift" )
    {
        o = new airliftOrder();
        listOfOrders->add(o);
    }
    else if ( order == "negotiate" )
    {
        o = new negotiateOrder();
        listOfOrders->add(o);
    }
    else
    {
        std::cout << "Invalid order" << std::endl;
        o = nullptr;
    }

}

// Setter
void Player::addPlayerTerritories(Territory* territory) {
    territories->push_back(territory);
    territory->owner = this;
}

void Player::setPlayerHandOfCards(Hand* handOfCards) {
    this->handOfCards = handOfCards;
}

void Player::setPlayerListOfOrders(OrdersList* listOfOrders) {
    this->listOfOrders = listOfOrders;

}

void Player::setArmyCount(int index, int armyCount){
    (*territories)[index]->armyCount = 50;
}

void Player::setReinforcementPool(int reinforcementPool) {
    this->reinforcementPool = reinforcementPool;
}


//operator assignment
Player& Player::operator=(const Player& p)
{
    if (this != &p)
    {
        this->name = p.name;
        this->territories = p.territories;
        this->handOfCards = p.handOfCards;
        this->listOfOrders = p.listOfOrders;
    }
    return *this;
}

//osstream operator
std::ostream& operator<<(std::ostream& os, const Player& p)
{
    os << p.name << "'s territories: " << std::endl;
    for (Territory* territory : *p.territories)
    {
        os << *territory << std::endl;
    }
    os << p.name << "'s hand of cards: " << *p.handOfCards << std::endl;
    os << p.name << "'s list of orders: " << *p.listOfOrders <<std::endl;
    os << p.name << "'s reinforcement pool: " << p.reinforcementPool << std::endl;

    return os;
}