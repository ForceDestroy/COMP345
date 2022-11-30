#include "Player.h"
#include "../Orders/Orders.h"

//Default constructor
Player::Player()
{
    name = "";
    territories = new std::vector<Territory*>();
    handOfCards = new Hand();
    listOfOrders = new OrdersList();
    reinforcementPool = 0;
    hasPlayedCard = false;
    hasDefended = false;
    hasAttacked = false;
    hasFinishedIssuingOrders = false;
    committedTerritories = new std::vector<Territory*>();
    attackedTerritories = new std::vector<Territory*>();
}

//Parameterized constructor
Player::Player(std::string name)
{
    this->name = name;
	this->territories = new std::vector<Territory*>();
	this->handOfCards = new Hand();
	this->listOfOrders = new OrdersList();
    this->reinforcementPool = 0;
    this->hasPlayedCard = false;
    this->hasDefended = false;
    this->hasAttacked = 3;
    this->hasFinishedIssuingOrders = false;
    this->committedTerritories = new std::vector<Territory*>();
    this->attackedTerritories = new std::vector<Territory*>();
    this->negotiateList = new std::vector<Player*>(3);
    this->hasConqTerritory = false;
}


//Parameterized constructor
Player::Player(std::vector<Territory*>* territories, Hand* handOfCards, OrdersList* listOfOrders, PlayerStrategy* strategy )
{
    this->name = "";
    this->territories = territories;
    this->handOfCards = handOfCards;
    this->listOfOrders = listOfOrders;
    this->reinforcementPool = 0;
    this->hasPlayedCard = false;
    this->hasDefended = false;
    this->hasAttacked = 1;
    this->hasFinishedIssuingOrders = false;
    this->committedTerritories = new std::vector<Territory*>();
    this->negotiateList = new std::vector<Player*>(3);
    this->hasConqTerritory = false;
    this->negotiateList = new std::vector<Player*>(3);
    this->hasConqTerritory = false;
    this->strategy = strategy;
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
std::vector<Territory*> Player::toAttack()
{
    return strategy->toAttack(this);
}
//Defend method
std::vector<Territory*> Player::toDefend()
{
    return strategy->toDefend(this);
}

//Check remaining number of territories and return whether player has lost
bool Player::hasLost() {
    return territories->size() == 0;
}

//Issue order method
void Player::issueOrder()
{
    strategy->issueOrder(this);
}
//To reset the params for the next IssueOrderPhase
void Player::resetIssueOrderPhase()
{
    hasPlayedCard = false;
    hasDefended = false;
    hasAttacked = false;
    hasFinishedIssuingOrders = false;
    committedTerritories->clear();
    attackedTerritories->clear();
    negotiateList->clear();
    hasConqTerritory = false;
}

//Check if the player is under negotiation
bool Player::truce(Player* player)
{
    for (Player* p : *negotiateList)
    {
        if (p == player)
            return true;
    }
    return false;
}

std::vector<Territory*>* Player::getTerritories() {
    return territories;
}

OrdersList* Player::getOrdersList() {
    return listOfOrders;
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

void Player::setReinforcementPool(int reinforcementPool) {
    this->reinforcementPool = reinforcementPool;
}

void Player::addNegotiateList(Player* player) {
    negotiateList->push_back(player);
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
        this->reinforcementPool = p.reinforcementPool;
        this->hasPlayedCard = p.hasPlayedCard;
        this->hasDefended = p.hasDefended;
        this->hasAttacked = p.hasAttacked;
        this->hasFinishedIssuingOrders = p.hasFinishedIssuingOrders;
        this->committedTerritories = p.committedTerritories;
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

void Player::removeTerritory(Territory* t) {
    territories->erase(remove(territories->begin(), territories->end(), t), territories->end());
}
