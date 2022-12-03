#include "PlayerStrategies.h"
#include <vector>
#include <ostream>
#include "../Orders/Orders.h"


#pragma region AggressivePlayerStrategy

//Default Constructor - Empty because Class has no properties
AggressivePlayerStrategy::AggressivePlayerStrategy() {}

//Copy Constructor - Empty because class has no properties
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& a) {}

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
    //Set the territories to attack and defend
    std::vector<Territory*> territoriesToDefend = toDefend(player);
    std::vector<Territory*> territoriesToAttack = toAttack(player);
    //If there are still reinforcements inside the pool, then keep deploying them
    if (player->reinforcementPool > 0)
    {
        //Deploy all reinforcements to strongest territory (found by toDefend)
        std::cout << "Player " << player->name << " creating Deploy Order of " << player->reinforcementPool << " units to territory " << territoriesToDefend.at(0)->name << std::endl;
        player->listOfOrders->add(new deployOrder(player, territoriesToDefend.at(0), player->reinforcementPool));
        player->reinforcementPool = 0;

        std::cout << "Player " << player->name << " has " << player->reinforcementPool << " reinforcements remaining" << std::endl;
    }
    //A player can play one card per phase
    else if (!player->hasPlayedCard && territoriesToAttack.size() != 0)
    {
        //If the player has a bomb or airlift card, play it
        if (player->handOfCards->listOfCards->size() > 0)
        {
            for (int i = 0; i < player->handOfCards->listOfCards->size(); i++) {
                switch (player->handOfCards->listOfCards->at(i)->type)
                {
                case bomb:
                {
                    std::cout << "Player " << player->name << " creating Order to play the following card " << *player->handOfCards->listOfCards->at(i) << std::endl;
                    int position = std::rand() % territoriesToAttack.size();
                    Territory* territoryToBomb = territoriesToAttack.at(position);

                    player->handOfCards->listOfCards->at(i)->Play(*player->handOfCards);
                    player->listOfOrders->add(new bombOrder(player, territoryToBomb));
                    player->hasPlayedCard = true;
                    return;
                }
                //Airlift considered aggressive because it strengthens strongest territory
                case airlift:
                {
                    std::cout << "Player " << player->name << " creating Order to play the following card " << *player->handOfCards->listOfCards->at(i) << std::endl;

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

                    player->hasPlayedCard = true;
                    return;
                }
                default:
                    break;
                }
            }

        }

    }
    else {
        //player can will advance to strongest territory from one adjacent territory
        if (!player->hasDefended)
        {
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
                        player->hasDefended = true;
                        //so that we don't defend and attack from the same territory
                        player->committedTerritories->push_back(neighbor);
                        return;
                    }
                }
            }
            //set defended to done if there are no territories to advance from
            player->hasDefended = true;
        }
        else if (!player->hasAttacked > 0 && territoriesToAttack.size() != 0)
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
                        std::cout << "Player " << player->name << " creating Advance Order to attack " << territoryToAttack->name << " from " << strongestT->name << std::endl;
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
}

//Resets the committed troups to 0
void AggressivePlayerStrategy::resetIssueOrderPhase() {
    committedTroups = 0;
}


AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& a)
{
    return *this;
}

std::ostream& operator<<(std::ostream& out, const AggressivePlayerStrategy& a) {
    out << "This Player is Aggressive" << std::endl;
    return out;
}
#pragma endregion