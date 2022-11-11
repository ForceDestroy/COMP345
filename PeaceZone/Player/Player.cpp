#include "Player.h"

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
    this->hasAttacked = false;
    this->hasFinishedIssuingOrders = false;
    this->committedTerritories = new std::vector<Territory*>();
}


//Parameterized constructor
Player::Player(std::vector<Territory*>* territories, Hand* handOfCards, OrdersList* listOfOrders)
{
    this->name = "";
    this->territories = territories;
    this->handOfCards = handOfCards;
    this->listOfOrders = listOfOrders;
    this->reinforcementPool = 0;
    this->hasPlayedCard = false;
    this->hasDefended = false;
    this->hasAttacked = false;
    this->hasFinishedIssuingOrders = false;
    this->committedTerritories = new std::vector<Territory*>();
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
    //getting neighbors of the territories to attack
    std::vector<Territory*> territoriesToAttack;
    for (int i = 0; i < territories->size(); i++)
    {
        for (int j = 0; j < territories->at(i)->neighbors.size(); j++)
        {
            if (territories->at(i)->neighbors.at(j)->owner != territories->at(i)->owner && 
            std::find(territoriesToAttack.begin(), territoriesToAttack.end(), territories->at(i)) == territoriesToAttack.end() && 
            territories->at(i)->neighbors.at(j)->armyCount <= territories->at(i)->armyCount)
            {
                territoriesToAttack.push_back(territories->at(i)->neighbors.at(j));
            }
        }
    }
    //If there are no territories to attack then it means you must focus on defending
    return territoriesToAttack;
}
//Defend method
std::vector<Territory*> Player::toDefend()
{
    //get all the territories to defend that the player owns
    std::vector<Territory*> territoriesToDefend;
    Territory* strongestTerritory = territories->at(0);
    for (int i = 0; i < territories->size(); i++)
    {
        for (int j = 0; j < territories->at(i)->neighbors.size(); j++)
        {
            if (territories->at(i)->neighbors.at(j)->owner != territories->at(i)->owner && 
                std::find(territoriesToDefend.begin(), territoriesToDefend.end(), territories->at(i)) == territoriesToDefend.end() && 
                territories->at(i)->neighbors.at(j)->armyCount >= territories->at(i)->armyCount)
            {
                territoriesToDefend.push_back(territories->at(i));
            }
        }
        if (territories->at(i)->armyCount > strongestTerritory->armyCount)
        {
            strongestTerritory = territories->at(i);
        }
    }
    //If it gets here, then it means there are no territory needed to be defended so put all reinforcements on the strongest territory to bolster defences
    if (territoriesToDefend.size() == 0)
    {
        territoriesToDefend.push_back(strongestTerritory);
    }
    return territoriesToDefend;
}

//Check remaining number of territories and return whether player has lost
bool Player::hasLost() {
    return territories->size() == 0;
}

//Issue order method
void Player::issueOrder()
{
    std::vector<Territory*> territoriesToDefend = toDefend();
    std::vector<Territory*> territoriesToAttack = toAttack();
    if (reinforcementPool > 0)
    {
        int position = std::rand() % territoriesToDefend.size();
        int armyCount = std::rand() % reinforcementPool/2 + 1;
        listOfOrders->add(new Deploy(territoriesToDefend.at(position), armyCount));
        reinforcementPool -= armyCount;
    }
    else if (!hasPlayedCard)
    {
        if (handOfCards->listOfCards->size() > 0)
        {
            Card* cardToPlay = handOfCards->listOfCards->at(0);
            cardToPlay->Play(*handOfCards, *listOfOrders);
        }
        hasPlayedCard = true;
    }
    else {
        if (!hasDefended)
        {
            for (auto defend: territoriesToDefend)
            {
                for (auto neighbor : defend->neighbors)
                {
                    if (std::find(territoriesToDefend.begin(), territoriesToDefend.end(), neighbor) == territoriesToDefend.end() && neighbor->armyCount > 1)
                    {
                        //new advance (neighbor sending units to defend)
                        listOfOrders->add(new Advance(defend, neighbor, (neighbor->armyCount)/2 +1));
                        hasDefended = true;
                        committedTerritories->push_back(neighbor);
                        return;
                    }
                }
            }
            hasDefended = true;
        }
        else if (!hasAttacked)
        {
            if (territoriesToAttack.size() > 0)
            {
                int position = std::rand() % territoriesToAttack.size();
                Territory* territoryToAttack = territoriesToAttack.at(position);
                for (auto neighbor : territoryToAttack->neighbors)
                {
                    if (neighbor->owner == this && std::find(committedTerritories->begin(), committedTerritories->end(), neighbor) == committedTerritories->end() && neighbor->armyCount > territoryToAttack->armyCount)
                    {
                        listOfOrders->add(new Advance(territoryToAttack, neighbor, neighbor->armyCount));
                        break;
                    }
                }
            }
            hasAttacked = true;
        }
        else
        {
            hasFinishedIssuingOrders = true;
        }
    }
}
void Player::resetIssueOrderPhase()
{
    hasPlayedCard = false;
    hasDefended = false;
    hasAttacked = false;
    hasFinishedIssuingOrders = false;
    committedTerritories->clear();
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