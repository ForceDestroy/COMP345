#include "PlayerStrategies.h"
#include <vector>
#include <ostream>
#include "../Orders/Orders.h"

std::ostream& operator<<(std::ostream& out, PlayerStrategy& p) {
    out << p.describe() << std::endl;
    return out;
}

#pragma region AggressivePlayerStrategy

//Default Constructor - Empty because Class has no properties
AggressivePlayerStrategy::AggressivePlayerStrategy() {
    type = "Aggressive";
}

//Copy Constructor - Empty because class has no properties
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& a) {
    this->type = a.type;
}

//Destructor - Empty because class has no properties
AggressivePlayerStrategy::~AggressivePlayerStrategy() {}

// toAttack method - Find all territories next to the strongest territory
std::vector<Territory*> AggressivePlayerStrategy::toAttack(Player* player) {
    std::vector<Territory*> territoriesToAttack;
    //To find the territories that can be attacked

    //Find the player's strongest territory
    Territory* strongestT = player->territories->at(0);
    for (int i = 0; i < player->territories->size(); i++)
    {
        if (player->territories->at(i)->armyCount > strongestT->armyCount)
            strongestT = player->territories->at(i);
    }

    for (int j = 0; j < strongestT->neighbors.size(); j++)
    {
        //Check if the neighbor is owned by another player
        //Check if the neighbor is not already in the list of territories to attack
        //Check if the army count of the territory to attack is less than the army count of the territory that is attacking to make it a valid attack
        if (strongestT->neighbors.at(j)->owner != strongestT->owner &&
            std::find(territoriesToAttack.begin(), territoriesToAttack.end(), strongestT) == territoriesToAttack.end() &&
            strongestT->neighbors.at(j)->armyCount < strongestT->armyCount)
        {
            territoriesToAttack.push_back(strongestT->neighbors.at(j));
        }
    }
    //If there are no territories to attack then it means you must focus on defending
    return territoriesToAttack;
}

//toDefend method only deploys to the strongest board
std::vector<Territory*> AggressivePlayerStrategy::toDefend(Player* player) {
    std::vector<Territory*> territoriesToDefend;
    //To find the territories that can be attacked

    //Find the player's strongest territory
    Territory* strongestT = player->territories->at(0);
    for (int i = 0; i < player->territories->size(); i++)
    {
        if (player->territories->at(i)->armyCount > strongestT->armyCount)
            strongestT = player->territories->at(i);
    }
    territoriesToDefend.push_back(strongestT);

    return territoriesToDefend;
}

//Nothing t
void AggressivePlayerStrategy::issueOrder(Player* player) {
    std::cout << std::endl << "******************************************" << std::endl;
    if (player->territories->size() == 0) {
        player->hasFinishedIssuingOrders = true;
        return;
    }
    //Set the territories to attack and defend
    std::vector<Territory*> territoriesToDefend = toDefend(player);
    std::vector<Territory*> territoriesToAttack = toAttack(player);
    //If there are still reinforcements inside the pool, then keep deploying them
    if (player->reinforcementPool > 0)
    {
        //Deploy all reinforcements to strongest territory (found by toDefend)
        std::cout << "Aggressive Player " << player->name << " creating Deploy Order of " << player->reinforcementPool << " units to their strongest territory " << territoriesToDefend.at(0)->name << std::endl;
        player->listOfOrders->add(new deployOrder(player, territoriesToDefend.at(0), player->reinforcementPool));
        player->reinforcementPool = 0;

        std::cout << "Aggressive Player " << player->name << " has " << player->reinforcementPool << " reinforcements remaining" << std::endl;
    }
    //A player can play one card per phase
    else if (!player->hasPlayedCard && territoriesToAttack.size() != 0)
    {
        //If the player has a bomb or airlift card, play it
        if (player->handOfCards->listOfCards->size() > 0)
        {
            player->hasPlayedCard = true;
            for (int i = 0; i < player->handOfCards->listOfCards->size(); i++) {
                switch (player->handOfCards->listOfCards->at(i)->type)
                {
                case bomb:
                {
                    std::cout << "Aggressive Player " << player->name << " creating Order to play the following card " << *player->handOfCards->listOfCards->at(i) << std::endl;
                    int position = std::rand() % territoriesToAttack.size();
                    Territory* territoryToBomb = territoriesToAttack.at(position);

                    player->handOfCards->listOfCards->at(i)->Play(*player->handOfCards);
                    player->listOfOrders->add(new bombOrder(player, territoryToBomb));
                    return;
                }
                //Airlift considered aggressive because it strengthens strongest territory
                case airlift:
                {
                    std::cout << "Aggressive Player " << player->name << " creating Order to play the following card " << *player->handOfCards->listOfCards->at(i) << std::endl;

                    Territory* territoryToAirlift = territoriesToDefend.at(0);
                    Territory* sourceTerritory = NULL;

                    for (auto territory : *player->territories)
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

                    player->handOfCards->listOfCards->at(i)->Play(*player->handOfCards);
                    player->listOfOrders->add(new airliftOrder(player, sourceTerritory, territoryToAirlift, sourceTerritory->armyCount / 2 + 1));

                    return;
                }
                default:
                    break;
                }
            }

        }

    }
    else 
        //player can will advance to strongest territory from one adjacent territory
        if (!player->hasDefended)
        {
            player->hasDefended = true;
            //go through the lists of territories to defend
            for (auto defend : territoriesToDefend)
            {
                //find the neighbor territory to provide troops to defend
                for (auto neighbor : defend->neighbors)
                {
                    //find a neighbor with army to advance
                    if (neighbor->armyCount > 1)
                    {
                        std::cout << "Aggressive Player " << player->name << " creating Advance Order to bolster their strongest territory " << defend->name << " from " << neighbor->name << std::endl;
                        //new advance (neighbor sending units to defend)
                        player->listOfOrders->add(new advanceOrder(player, neighbor, defend, (neighbor->armyCount) / 2 + 1));
                        //so that we don't defend and attack from the same territory
                        player->committedTerritories->push_back(neighbor);
                        return;
                    }
                }
            }
        }
        else if (!player->hasAttacked  && territoriesToAttack.size() != 0)
        {
            //only attack if there are territories to attack
            if (territoriesToAttack.size() > 0)
            {

                for (auto territoryToAttack : territoriesToAttack)
                {
                    Territory* strongestT = territoriesToDefend.at(0);

                    int troupsToAdvance = territoryToAttack->armyCount + 2;
                    int troupsLeft = strongestT->armyCount - committedTroups;
                    if (std::find(player->attackedTerritories->begin(), player->attackedTerritories->end(), territoryToAttack) == player->attackedTerritories->end() &&
                        troupsToAdvance <= troupsLeft)
                    {
                        std::cout << "Aggressive Player " << player->name << " creating Advance Order to attack " << territoryToAttack->name << " from " << strongestT->name << std::endl;
                        player->listOfOrders->add(new advanceOrder(player, strongestT, territoryToAttack, troupsToAdvance));
                        player->attackedTerritories->push_back(territoryToAttack);
                        committedTroups += troupsToAdvance;
                        return;
                    }

                }
            }
            player->hasAttacked = true;
        }
        //when the player is done with all the orders
        else
        {
            player->hasFinishedIssuingOrders = true;
        }
    
}

//Resets the committed troups to 0
void AggressivePlayerStrategy::resetIssueOrderPhase() {
    committedTroups = 0;
}


AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& a)
{
    if (this != &a)
    {
        this->type = a.type;
    }
    return *this;
}

std::string AggressivePlayerStrategy::describe() {
    return "This Player is Neutral";
}
#pragma endregion

#pragma region BenevolentPlayerStrategy

//Default Constructor - Empty because Class has no properties
BenevolentPlayerStrategy::BenevolentPlayerStrategy() {
    type = "Benevolent";
}

//Copy Constructor - Empty because class has no properties
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& b) {
    this->type = b.type;
}

//Destructor - Empty because class has no properties
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

// toAttack method - Return a List with 1 enemy territory for diplomacy purposes
std::vector<Territory*> BenevolentPlayerStrategy::toAttack(Player* player) {
    std::vector<Territory*> territoriesToAttack;
    //To find the territories that can be attacked
    for (int i = 0; i < player->territories->size(); i++)
    {
        //Go through each neighbor of the territories that the player owns
        for (int j = 0; j < player->territories->at(i)->neighbors.size(); j++)
        {
            //Check if the neighbor is owned by another player
            if (player->territories->at(i)->neighbors.at(j)->owner != player->territories->at(i)->owner )
            {
                territoriesToAttack.push_back(player->territories->at(i)->neighbors.at(j));
                //return after finding 1 enemy territory
                return territoriesToAttack;
            }
        }
    }
    return territoriesToAttack;
}

//toDefend method benevolent player focuses on protecting its weakest territories
std::vector<Territory*> BenevolentPlayerStrategy::toDefend(Player* player) {
    std::vector<Territory*> territoriesToDefend;
    if (player->territories->size() == 0) {
        return territoriesToDefend;
    }

    //Find the average army count of the player's territories
    int totalTroups = 0;
    for (int i = 0; i < player->territories->size(); i++)
    {
        totalTroups += player->territories->at(i)->armyCount;
    }
    int average = totalTroups / player->territories->size();

    //Reinforce territories weaker than the average
    for (int i = 0; i < player->territories->size(); i++)
    {
        if(player->territories->at(i)->armyCount <= average)
        {
            territoriesToDefend.push_back(player->territories->at(i));
        }
    }

    return territoriesToDefend;
}


void BenevolentPlayerStrategy::issueOrder(Player* player) {
    std::cout << std::endl << "******************************************" << std::endl;
    if (player->territories->size() == 0) {
        player->hasFinishedIssuingOrders = true;
        return;
    }
    //Set the territories to attack and defend
    std::vector<Territory*> territoriesToDefend = toDefend(player);
    std::vector<Territory*> territoriesToAttack = toAttack(player);
    //If there are still reinforcements inside the pool, then keep deploying them
    
    if (player->reinforcementPool > 0)
    {
        //find a random territory to deploy to
        std::srand((unsigned)std::time(0));
        int position = std::rand() % territoriesToDefend.size();
        //find a random number of armies to deploy
        std::srand((unsigned)std::time(0));
        int armyCount = (std::rand() % player->reinforcementPool) / 2 + 1;

        std::cout << "Benevolent Player " << player->name << " creating Deploy Order of " << armyCount << " units to territory " << territoriesToDefend.at(position)->name << std::endl;
        player->listOfOrders->add(new deployOrder(player, territoriesToDefend.at(position), armyCount));
        player->reinforcementPool -= armyCount;

        std::cout << "Benevolent Player " << player->name << " has " << player->reinforcementPool << " reinforcements remaining" << std::endl;
    }
    //A player can play one card per phase
    else if (!player->hasPlayedCard)
    {
        player->hasPlayedCard = true;
        //If the player has a bomb or airlift card, play it
        if (player->handOfCards->listOfCards->size() > 0)
        {
            for (int i = 0; i < player->handOfCards->listOfCards->size(); i++) {
                switch (player->handOfCards->listOfCards->at(i)->type)
                {
                case airlift:
                {
                    int position = std::rand() % territoriesToDefend.size();
                    Territory* territoryToAirlift = territoriesToDefend.at(position);
                    Territory* sourceTerritory = NULL;

                    for (auto territory : *player->territories)
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
                    player->handOfCards->listOfCards->at(i)->Play(*player->handOfCards);
                    player->listOfOrders->add(new airliftOrder(player, sourceTerritory, territoryToAirlift, sourceTerritory->armyCount / 2 + 1));

                    return;
                }
                case blockade:
                {
                    std::cout << "Benevolent Player " << player->name << " creating Order to play the following card " << *player->handOfCards->listOfCards->at(i) << std::endl;
                    int position = std::rand() % territoriesToDefend.size();
                    Territory* territoryToBlockade = territoriesToDefend.at(position);
                    player->handOfCards->listOfCards->at(i)->Play(*player->handOfCards);
                    player->listOfOrders->add(new blockadeOrder(player, territoryToBlockade));
                    return;
                }
                case diplomacy:
                {
                    if(territoriesToAttack.size()>0)
                    {
                        std::cout << "Benevolent Player " << player->name << " creating Order to play the following card " << *player->handOfCards->listOfCards->at(i) << std::endl;
                        player->handOfCards->listOfCards->at(i)->Play(*player->handOfCards);
                        player->listOfOrders->add(new negotiateOrder(player, territoriesToAttack[0]->owner));
                        return;
                    }
                }
                default:
                    break;
                }
            }

        }

    }
    else 
        //player can advance to defend one of it's territories
        if (!player->hasDefended)
        {
            player->hasDefended = true;
            //go through the lists of territories to defend
            for (auto defend : territoriesToDefend)
            {
                //find the neighbor territory to provide troops to defend
                for (auto neighbor : defend->neighbors)
                {
                    //find a neighbor with army to advance
                    if (neighbor->armyCount > 1)
                    {
                        std::cout << "Player " << player->name << " creating Advance Order to defend " << defend->name << " from " << neighbor->name << std::endl;
                        //new advance (neighbor sending units to defend)
                        player->listOfOrders->add(new advanceOrder(player, neighbor, defend, (neighbor->armyCount) / 2 + 1));
                        
                        //so that we don't defend and attack from the same territory
                        player->committedTerritories->push_back(neighbor);
                        return;
                    }
                }
            }
        }
        //when the player is done with all the orders
        else
        {
            player->hasFinishedIssuingOrders = true;
        }
    
}

//Nothing to reset for this strategy
void BenevolentPlayerStrategy::resetIssueOrderPhase() {
}


BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& a)
{
    if (this != &a)
    {
        this->type = a.type;
    }
    return *this;
}

std::string BenevolentPlayerStrategy::describe() {
    return "This Player is Neutral";
}
#pragma endregion

#pragma region NeutralPlayerStrategy

//Default Constructor - Empty because Class has no properties
NeutralPlayerStrategy::NeutralPlayerStrategy() {
    type = "Neutral";
}

//Copy Constructor - Empty because class has no properties
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& n) {
    this->type = n.type;
}

//Destructor - Empty because class has no properties
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

// toAttack method - Return empty list because neutral player does nothing
std::vector<Territory*> NeutralPlayerStrategy::toAttack(Player* player) {
    std::vector<Territory*> territoriesToAttack;

    return territoriesToAttack;
}

//toDefend method - Return nothing because Neutral player does nothing
std::vector<Territory*> NeutralPlayerStrategy::toDefend(Player* player) {
    std::vector<Territory*> territoriesToDefend;
   

    return territoriesToDefend;
}


//Neutral player ends its turn without issuing any orders
void NeutralPlayerStrategy::issueOrder(Player* player) {
    
    player->hasFinishedIssuingOrders = true;
}

//Nothing to reset for this strategy
void NeutralPlayerStrategy::resetIssueOrderPhase() {
}


NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& n)
{
    if (this != &n)
    {
        this->type = n.type;
    }
    return *this;

}

std::string NeutralPlayerStrategy::describe() {
    return "This Player is Neutral" ;
}
#pragma endregion

#pragma region CheaterPlayerStrategy

//Default Constructor - Empty because Class has no properties
CheaterPlayerStrategy::CheaterPlayerStrategy() {
    type = "Cheater";
    hasCheated = false;
}

//Copy Constructor - Empty because class has no properties
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& n) {
    this->type = n.type;
    this->hasCheated = n.hasCheated;
}

//Destructor - Empty because class has no properties
CheaterPlayerStrategy::~CheaterPlayerStrategy() {}

// toAttack method - Returns all its neighbor territories for cheating purposes
std::vector<Territory*> CheaterPlayerStrategy::toAttack(Player* player) {

    std::vector<Territory*> territoriesToAttack;
    //To find the territories that can be attacked
    for (int i = 0; i < player->territories->size(); i++)
    {
        //Go through each neighbor of the territories that the player owns
        for (int j = 0; j < player->territories->at(i)->neighbors.size(); j++)
        {
            //Check if the neighbor is owned by another player
            //Check if the neighbor is not already in the list of territories to attack
            if (player->territories->at(i)->neighbors.at(j)->owner != player->territories->at(i)->owner &&
                std::find(territoriesToAttack.begin(), territoriesToAttack.end(), player->territories->at(i)) == territoriesToAttack.end())
            {
                territoriesToAttack.push_back(player->territories->at(i)->neighbors.at(j));
            }
        }
    }
    return territoriesToAttack;
}

//toDefend method - Defends and Deploys as normal
std::vector<Territory*> CheaterPlayerStrategy::toDefend(Player* player) {
    //get all the territories to defend that the player owns
    std::vector<Territory*> territoriesToDefend;
    //Setting the first territory as the strongest as default for now
    Territory* strongestTerritory = player->territories->at(0);
    //To find the territories that can be defended
    for (int i = 0; i < player->territories->size(); i++)
    {
        //Go through each neighbor of the territories that the player owns
        for (int j = 0; j < player->territories->at(i)->neighbors.size(); j++)
        {
            //Check if the neighbor is owned by another player to warrant defending from an attack
            //Check if the neighbor is not already in the list of territories to defend
            //Check if the army count of the enemy neighbor is greater than the army count of the territory that is defending to give reason for defending
            if (player->territories->at(i)->neighbors.at(j)->owner != player->territories->at(i)->owner &&
                std::find(territoriesToDefend.begin(), territoriesToDefend.end(), player->territories->at(i)) == territoriesToDefend.end() &&
                player->territories->at(i)->neighbors.at(j)->armyCount >= player->territories->at(i)->armyCount)
            {
                territoriesToDefend.push_back(player->territories->at(i));
            }
        }
        //To find the strongest territory to defend
        if (player->territories->at(i)->armyCount > strongestTerritory->armyCount)
        {
            strongestTerritory = player->territories->at(i);
        }
    }
    //If it gets here, then it means there are no territory needed to be defended so put all reinforcements on the strongest territory to bolster defences
    if (territoriesToDefend.size() == 0)
    {
        territoriesToDefend.push_back(strongestTerritory);
    }
    return territoriesToDefend;
}


//Cheater player ends its turn without issuing any orders
void CheaterPlayerStrategy::issueOrder(Player* player) {
    std::cout << std::endl << "******************************************" << std::endl;
    //Set the territories to attack and defend
    std::vector<Territory*> territoriesToDefend = toDefend(player);
    std::vector<Territory*> territoriesToAttack = toAttack(player);
    if (!hasCheated) {
        for (auto t : territoriesToAttack) 
        {
            std::cout << "Cheater Player " << player->name << " stealing territory " << t->name << std::endl;
            t->owner->removeTerritory(t);
            t->owner = player;
            player->territories->push_back(t);
        }
        hasCheated = true;
    }
    //If there are still reinforcements inside the pool, then keep deploying them
    else if (player->reinforcementPool > 0)
    {
        //find a random territory to deploy to
        std::srand((unsigned)std::time(0));
        int position = std::rand() % territoriesToDefend.size();
        //find a random number of armies to deploy
        std::srand((unsigned)std::time(0));
        int armyCount = (std::rand() % player->reinforcementPool) / 2 + 1;

        std::cout << "Cheater Player " << player->name << " creating Deploy Order of " << armyCount << " units to territory " << territoriesToDefend.at(position)->name << std::endl;
        player->listOfOrders->add(new deployOrder(player, territoriesToDefend.at(position), armyCount));
        player->reinforcementPool -= armyCount;

        std::cout << "Cheater Player " << player->name << " has " << player->reinforcementPool << " reinforcements remaining" << std::endl;
    }
    else
        //player can will advance to strongest territory from one adjacent territory
        if (!player->hasDefended)
        {
            player->hasDefended = true;
            //go through the lists of territories to defend
            for (auto defend : territoriesToDefend)
            {
                //find the neighbor territory to provide troops to defend
                for (auto neighbor : defend->neighbors)
                {
                    //find a neighbor with army to advance
                    if (neighbor->armyCount > 1)
                    {
                        std::cout << "Cheater Player " << player->name << " creating Advance Order to bolster their strongest territory " << defend->name << " from " << neighbor->name << std::endl;
                        //new advance (neighbor sending units to defend)
                        player->listOfOrders->add(new advanceOrder(player, neighbor, defend, (neighbor->armyCount) / 2 + 1));
                        //so that we don't defend and attack from the same territory
                        player->committedTerritories->push_back(neighbor);
                        return;
                    }
                }
            }
           
        }
        //when the player is done with all the orders
        else
        {
            player->hasFinishedIssuingOrders = true;
        }
    
}

//Cheater to reset for this strategy
void CheaterPlayerStrategy::resetIssueOrderPhase() {
    hasCheated = false;
}


CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& n)
{
    if (this != &n)
    {
        this->type = n.type;
    }
    return *this;

}

std::string CheaterPlayerStrategy::describe() {
    return "This Player is a Cheater";
}
#pragma endregion