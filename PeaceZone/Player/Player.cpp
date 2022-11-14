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
Player::Player(std::vector<Territory*>* territories, Hand* handOfCards, OrdersList* listOfOrders)
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
    std::vector<Territory*> territoriesToAttack;
    //To find the territories that can be attacked
    for (int i = 0; i < territories->size(); i++)
    {
        //Go through each neighbor of the territories that the player owns
        for (int j = 0; j < territories->at(i)->neighbors.size(); j++)
        {
            //Check if the neighbor is owned by another player
            //Check if the neighbor is not already in the list of territories to attack
            //Check if the army count of the territory to attack is less than the army count of the territory that is attacking to make it a valid attack
            if (territories->at(i)->neighbors.at(j)->owner != territories->at(i)->owner && 
                std::find(territoriesToAttack.begin(), territoriesToAttack.end(), territories->at(i)) == territoriesToAttack.end() && 
                territories->at(i)->neighbors.at(j)->armyCount < territories->at(i)->armyCount)
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
    //Setting the first territory as the strongest as default for now
    Territory* strongestTerritory = territories->at(0);
    //To find the territories that can be defended
    for (int i = 0; i < territories->size(); i++)
    {
        //Go through each neighbor of the territories that the player owns
        for (int j = 0; j < territories->at(i)->neighbors.size(); j++)
        {
            //Check if the neighbor is owned by another player to warrant defending from an attack
            //Check if the neighbor is not already in the list of territories to defend
            //Check if the army count of the enemy neighbor is greater than the army count of the territory that is defending to give reason for defending
            if (territories->at(i)->neighbors.at(j)->owner != territories->at(i)->owner && 
                std::find(territoriesToDefend.begin(), territoriesToDefend.end(), territories->at(i)) == territoriesToDefend.end() && 
                territories->at(i)->neighbors.at(j)->armyCount >= territories->at(i)->armyCount)
            {
                territoriesToDefend.push_back(territories->at(i));
            }
        }
        //To find the strongest territory to defend
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
    //Set the territories to attack and defend
    std::vector<Territory*> territoriesToDefend = toDefend();
    std::vector<Territory*> territoriesToAttack = toAttack();
    //If there are still reinforcements inside the pool, then keep deploying them
    if (reinforcementPool > 0)
    {
        //find a random territory to deploy to
        std::srand((unsigned) std::time(0));
        int position = std::rand() % territoriesToDefend.size();
        //find a random number of armies to deploy
        std::srand((unsigned) std::time(0));
        int armyCount = (std::rand() % reinforcementPool)/2 + 1;

        std::cout << "Player " << name << " creating Deploy Order of "<< armyCount << " units to territory "<< territoriesToDefend.at(position)->name << std::endl;
        listOfOrders->add(new deployOrder(this,territoriesToDefend.at(position), armyCount));
        reinforcementPool -= armyCount;

        std::cout << "Player " << name << " has " << reinforcementPool << " reinforcements remaining" << std::endl;
    }
    //A player can play one card per phase
    else if (!hasPlayedCard && territoriesToAttack.size() != 0)
    {
        //If the player has a card, then play the first one
        if (handOfCards->listOfCards->size() > 0)
        {
            int position = std::rand() % handOfCards->listOfCards->size();
            Card* cardToPlay = handOfCards->listOfCards->at(position);
            std::cout << "Player " << name << " creating Order to play the following card " << *cardToPlay << std::endl;

            switch (cardToPlay->Play(*handOfCards))
            {
            case bomb:
            {
                int position = std::rand() % territoriesToAttack.size();
                Territory* territoryToBomb = territoriesToAttack.at(position);

                listOfOrders->add(new bombOrder(this, territoryToBomb));
                break;
            }
            case blockade:
            {
                int position = std::rand() % territoriesToDefend.size();
                Territory* territoryToBlockade = territoriesToDefend.at(position);

                listOfOrders->add(new blockadeOrder(this, territoryToBlockade));
                break;
            }
            case airlift:
            {
                int position = std::rand() % territoriesToDefend.size();
                Territory* territoryToAirlift = territoriesToDefend.at(position);
                Territory* sourceTerritory = NULL;

                for (auto territory : *territories)
                {
                    if (std::find(territoriesToDefend.begin(), territoriesToDefend.end(), territory) == territoriesToDefend.end() && territory->armyCount > 1)
                    {
                        sourceTerritory = territory;
                        break;
                    }
                }

                if (sourceTerritory == NULL) {
                    sourceTerritory = territoryToAirlift;
                }

                listOfOrders->add(new airliftOrder(this, sourceTerritory, territoryToAirlift, sourceTerritory->armyCount/2+1));

                break;
            }
            case diplomacy:
            {
                listOfOrders->add(new negotiateOrder(this, territoriesToAttack[0]->owner));
                break;
            }
            case reinforcement:
            {
                //Add more reinforcements to the player
                break;
            }
            default:
                break;
            }
        }
        hasPlayedCard = true;
    }
    else {
        //player can attack and defend once per phase
        if (!hasDefended)
        {
            //go through the lists of territories to defend
            for (auto defend: territoriesToDefend)
            {
                //find the neighbor territory to provide troops to defend
                for (auto neighbor : defend->neighbors)
                {
                    //find a neighbor with army to advance
                    if ( neighbor->armyCount > 1)
                    {
                        std::cout << "Player " << name << " creating Advance Order to defend " << defend->name << " from " << neighbor->name << std::endl;
                        //new advance (neighbor sending units to defend)
                        listOfOrders->add(new advanceOrder(this, neighbor, defend, (neighbor->armyCount)/2 +1));
                        hasDefended = true;
                        //so that we don't defend and attack from the same territory
                        committedTerritories->push_back(neighbor);
                        return;
                    }
                }
            }
            hasDefended = true;
        }
        else if (!hasAttacked > 0 && territoriesToAttack.size() != 0)
        {
            //only attack if there are territories to attack
            if (territoriesToAttack.size() > 0)
            {
                //find a random territory to attack
               // std::srand((unsigned) std::time(0));
               // int position = std::rand() % territoriesToAttack.size();
               // Territory* territoryToAttack = territoriesToAttack.at(position);

                for (auto territoryToAttack : territoriesToAttack)
                {
                    //find a valid neighbor territory to attack from
                    for (auto neighbor : territoryToAttack->neighbors)
                    {
                        //check if the owner of the territory belongs to the current player attacking
                        //check if the territory is not in the list of committed territories
                        //check if the army count of the territory attacking is higher than the army count of the territory getting attacked to make it a valid attack
                        if (neighbor->owner == this && std::find(committedTerritories->begin(), committedTerritories->end(), neighbor) == committedTerritories->end() 
                            && std::find(attackedTerritories->begin(), attackedTerritories->end(), territoryToAttack) == attackedTerritories->end() && neighbor->armyCount > territoryToAttack->armyCount)
                        {
                            std::cout << "Player " << name << " creating Advance Order to attack " << territoryToAttack->name << " from " << neighbor->name << std::endl;
                            listOfOrders->add(new advanceOrder(this, neighbor, territoryToAttack, neighbor->armyCount));
                            committedTerritories->push_back(neighbor);
                            attackedTerritories->push_back(territoryToAttack);
                            return;
                        }
                    }
                }
            }
            hasAttacked = true;
        }
        //when the player is done with all the orders
        else
        {
            hasFinishedIssuingOrders = true;
        }
    }
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
