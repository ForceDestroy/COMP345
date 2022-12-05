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

#pragma region HumanPlayerStrategy
// Default constructor
HumanPlayerStrategy::HumanPlayerStrategy()
{
    type = "Human";
}

// Copy constructor
HumanPlayerStrategy::HumanPlayerStrategy(HumanPlayerStrategy* hps)
{
    this->terToAttack = hps->terToAttack;
    this->terToDefend = hps->terToDefend;
    type = "Human";
}

// Destructor
HumanPlayerStrategy::~HumanPlayerStrategy()
{
    terToAttack.~vector();
    terToDefend.~vector();
}

// Returns territories being attacked/bombed
std::vector<Territory*> HumanPlayerStrategy::toAttack(Player* p)
{
    return terToAttack;
}

// Returns territories being deployed to, defended, blockade, airlift
std::vector<Territory*> HumanPlayerStrategy::toDefend(Player* p)
{
    return terToDefend;
}

// Takes a player and a territory name as parameters
// If the player owns the territory with that name, return the terrritory
// If not return null
Territory* HumanPlayerStrategy::getTerByName(Player* p, std::string name)
{
    for (int i = 0; i < p->territories->size(); i++)
    {
        if (p->territories->at(i)->name == name)
            return p->territories->at(i);
    }
    return NULL;
}

// This method returns a list of players that own territories neighboring the player's territories
std::vector<Player*> HumanPlayerStrategy::getNearbyPlayers(Player* p)
{
    std::vector<Player*> temp;
    bool onList = false;
    for (int i = 0; i < p->territories->size(); i++)
    {
        for (int j = 0; j < p->territories->at(i)->neighbors.size(); j++)
        {
            if (p->territories->at(i)->neighbors.at(j)->owner != p)
            {
                if (temp.empty())
                    temp.push_back(p->territories->at(i)->neighbors.at(j)->owner);
                else
                {
                    for (int k = 0; k < temp.size(); k++)
                    {
                        if (temp.at(k) == p->territories->at(i)->neighbors.at(j)->owner)
                        {
                            onList = true;
                        }
                    }
                    if (!onList)
                        temp.push_back(p->territories->at(i)->neighbors.at(j)->owner);
                }
            }
        }
    }
    return temp;
}

// Receives a string input of a name of a territory that the player owns
// If the user enters a wrong name, they are asked again until they get a correct one or the choose to go back
// The user can choose to go back if they type "back"
std::string HumanPlayerStrategy::getName(Player* p)
{
    std::string terName;
    bool nameFound = false;
    std::cout << "Enter a territory name(\"back\" to go back): " << std::endl;
    while (!nameFound)
    {
        std::cin >> terName;
        if (terName == "back")
            return terName;
        for (int i = 0; i < p->territories->size(); i++)
        {
            if (terName == p->territories->at(i)->name)
            {
                return terName;
            }
        }
        std::cout << "Territory name not found. Try again (\"back\" to go back): " << std::endl;
    }
}

// Receives an input from the user that is the number of troops to be used in an order
// Input must be non-negative and less than a limit amount (May be amount of reserve units or current troops on a territory)
// Input is looped until a correct number is entered
// User may go back by typing 0
int HumanPlayerStrategy::getTroops(Player* p)
{
    int troops = 0;
    std::cout << "Enter number of troops to deploy (0 to go back): " << std::endl;
    std::cin >> troops;
    while (troops < 0)
    {
        std::cout << "Invalid troop number. Try again (0 to go back): " << std::endl;
        std::cin >> troops;
    }
    return troops;
}

// This function makes the user choose an action after the deploy phase
// Type 'a' to attack
// Type 'd' to defend
// Type 'c' to play a card
// Type 's' to skip. This will end a player's issue order phase
// This will looop until the player chooses a valid option
char HumanPlayerStrategy::getOption()
{
    char option = ' ';
    std::cout << "Please enter your option: 'a' to attack, 'd' to defend, 'c' to play a card, 's' to skip" << std::endl;
    std::cin >> option;
    while (!(option == 'a' || option == 'd' || option == 's' || option == 'c'))
    {
        std::cout << "Invalid option, please try again." << std::endl;
        std::cout << "Please enter your option 'a' to attack, 'd' to defend, 'c' to play a card, 's' to skip" << std::endl;
        std::cin >> option;
    }
    return option;
}


// This is the main funciton of the class
// This function starts by beginning the deploy phase
// Then it will go to ask players for their actions until the user decides to finish
void HumanPlayerStrategy::issueOrder(Player* p)
{
    
    std::cout << "Human Player: " << p->name << std::endl;
    std::string name;
    int troops;
    // Start of deploy orders
    // Looped until their are no more reserve troops
    if (p->territories->size() == 0)
    {
        p->hasFinishedIssuingOrders = true;
    }
    else if (p->reinforcementPool > 0)
    {
        std::cout << "==============" << std::endl;
        std::cout << "Human player " << p->name << " has " << p->reinforcementPool << " troops remainging." << std::endl;
        std::cout << "Human player " << p->name << " territories are: " << std::endl;
        for (int i = 0; i < p->territories->size(); i++)
        {
            std::cout << p->territories->at(i)->name << std::endl;
        }
        std::cout << "Enter territory to reinforce." << std::endl;
        // Get the name of an owned territory
    getTerritoryName:
        name = getName(p);
        while (name == "back")
        {
            std::cout << "Over reinforcement pool. Try again." << std::endl;
            name = getName(p);
        }
        // Select the number of troops to send
        troops = getTroops(p);
        while (troops > p->reinforcementPool)
        {
            troops = getTroops(p);
        }
        // If the player enters "back" for the name or "0" for troops, the program will go back to asking for the name
        if (troops == 0)
            goto getTerritoryName;
        // Adds a deploy order of "troops" troops to the territory with "name" name
        p->listOfOrders->add(new deployOrder(p, getTerByName(p, name), troops));
        p->reinforcementPool -= troops;
        terToDefend.push_back(getTerByName(p, name));
        std::cout << "Order added." << std::endl;
    }
    else {
        while (!p->hasFinishedIssuingOrders) {
            // bool done is used to check if players are finished with their issue order phaes
            bool done = false;
            // source and target denotes the source and target territory of an order
            Territory* source = NULL;
            Territory* target = NULL;
            bool nameValid = false, validSourceAndTarget = false;;
            std::cout << "==============" << std::endl;
            // Different cases depending on the player action
            switch (getOption())
            {
                // Player wants to play a card
            case 'c':
            {
                // Checks if a player has a card or player has already played a card
                if (p->handOfCards->listOfCards->size() == 0)
                    std::cout << "You do not have any cards." << std::endl;
                else if (p->hasPlayedCard)
                    std::cout << "Player can not player more than 1 card per turn." << std::endl;
                else
                {
                    // Prints the player current hand of cards
                    std::cout << "Player's current hand of card: " << std::endl;
                    std::cout << *p->handOfCards << std::endl;
                    // Let the player choose the card to play through the index of the hand
                    // Example if the player has 3 cards then the player can choose 1, 2 or 3 corresponding to the card's index in the hand + 1
                    std::cout << "Please choose a card number to play, from 1 to " << p->handOfCards->listOfCards->size() << std::endl;
                    std::cout << "Type 0 to go back." << std::endl;
                    int cardNum = 0;
                    std::cin >> cardNum;
                    // Checks if the user enters a valid number (between 1 and the hand size)
                    while (cardNum > p->handOfCards->listOfCards->size() || cardNum <= 0)
                    {
                        if (cardNum == 0)
                            // goto finish will make it so that the user return to getOption() to choose a different action
                            goto finish;
                        std::cout << "Wrong number, please try again (0 to go back): ";
                        std::cin >> cardNum;
                    }
                    Card* toPlay = p->handOfCards->listOfCards->at(cardNum - 1);
                    // Different cases depending on which card the player decides to play
                    // Cases: bomb, airlift, blockade, negotiate
                    switch (toPlay->Play(*p->handOfCards))
                    {
                        // Bomb card
                    case bomb:
                    {
                        std::cout << "You've chosen to play the bomb card." << std::endl;
                        std::cout << "Available targets: " << std::endl;
                        for (int i = 0; i < p->territories->size(); i++)
                        {
                            for (int j = 0; j < p->territories->at(i)->neighbors.size(); j++)
                            {
                                if (p->territories->at(i)->neighbors.at(j)->owner != p)
                                    std::cout << p->territories->at(i)->neighbors.at(j)->name << std::endl;
                            }
                        }
                        std::cout << "Enter bomb target territory name (\"back\" to go back): " << std::endl;
                        std::cin >> name;
                        nameValid = false;
                        // Looped until valid name is entered or user choose to go back
                        while (!nameValid)
                        {
                            // Go back to getOption() if the player types "back"
                            if (name == "back")
                                goto finish;
                            // Checks if the territory is not owned by the player and is adjacent to an owned territory
                            for (int i = 0; i < p->territories->size(); i++)
                            {
                                for (Territory* n : p->territories->at(i)->neighbors)
                                {
                                    if (name == n->name && getTerByName(p, name) == NULL)
                                    {
                                        target = n;
                                        nameValid = true;
                                    }
                                }
                            }
                            if (!nameValid)
                                std::cout << "Not valid territory, try again(\"back\" to go back): " << std::endl;
                            std::cin >> name;
                        }
                        // Adds a bomb order and adds a the target territory to terToAttack
                        p->listOfOrders->add(new bombOrder(p, target));
                        terToAttack.push_back(getTerByName(p, name));
                        std::cout << "Bomb order added." << std::endl;
                        break;
                    }
                    // Blockade card
                    case blockade:
                    {
                        std::cout << "You've chosen to play the blockade order." << std::endl;
                        std::cout << "Available targets: " << std::endl;
                        for (int i = 0; i < p->territories->size(); i++)
                        {
                            std::cout << p->territories->at(i)->name << std::endl;
                        }
                        std::cout << "Enter blockade target territory name (\"back\" to go back): " << std::endl;
                        // Get target territory name (must be owned by player)
                        name = getName(p);
                        // Add a blockade order an add target territory to terToDefend
                        p->listOfOrders->add(new blockadeOrder(p, getTerByName(p, name)));
                        terToDefend.push_back(getTerByName(p, name));
                        std::cout << "Blockade order added." << std::endl;
                        break;
                    }
                    //Airlift card
                    case airlift:
                    {
                        std::cout << "You've chosen to play the airlift order." << std::endl;
                        std::cout << "Available targets: " << std::endl;
                        for (int i = 0; i < p->territories->size(); i++)
                        {
                            std::cout << p->territories->at(i)->name << std::endl;
                        }
                        std::cout << "Enter airlift target territory name (\"back\" to go back): " << std::endl;
                        // Checks if the entered source and target territory is valid
                        nameValid = false;
                        name = "";
                        source = NULL;
                        target = NULL;
                        // looped until valid source and target or go back
                        while (!nameValid)
                        {
                            std::cout << "Select target to send troops from. " << std::endl;
                            name = getName(p);
                            if (name == "back")
                                goto finish;
                            source = getTerByName(p, name);

                            std::cout << "Select target to send troops to. " << std::endl;
                            name = getName(p);
                            if (name != "back")
                                // If name == "back" then go back to selecting source target
                            {
                                target = getTerByName(p, name);
                                if (source == target) // If the source and target territory is the same, go back to selecting source territory
                                {
                                    std::cout << "Invalid input, try again (\"back\" go to back): " << std::endl;
                                }
                                else
                                {
                                    std::cout << "Enter number of troops to send. " << std::endl;
                                    troops = getTroops(p);
                                    if (troops != 0)
                                        nameValid = true; // exit loop
                                    // IF troops == 0, go back to selecting source territory
                                }
                            }
                        }
                        // Adds a new airlift order and adds the target territory to terToDefend
                        p->listOfOrders->add(new airliftOrder(p, source, target, troops));
                        terToDefend.push_back(getTerByName(p, name));
                        std::cout << "Airlift order added." << std::endl;
                        break;
                    }
                    // Negotiate card
                    case diplomacy:
                    {
                        std::cout << "You've chosen to play the negotiate card." << std::endl;
                        std::cout << "Available targets: " << std::endl;
                        for (int i = 0; i < getNearbyPlayers(p).size(); i++)
                        {
                            std::cout << getNearbyPlayers(p).at(i)->name << std::endl;
                        }
                        std::cout << "Please enter a player to negotiate with: " << std::endl;
                        name = "";
                        nameValid = false;
                        // Looped until a valid player is acquired or going back
                        while (!nameValid)
                        {
                            std::cin >> name;
                            // Checks for the player name on the list of players and checks if the target player is not the one playing the card
                            for (Player* n : getNearbyPlayers(p))
                            {
                                if (n->name == name && p->name != name)
                                {
                                    nameValid = true;
                                    p->listOfOrders->add(new negotiateOrder(p, n));
                                }
                            }
                            if (!nameValid)
                                std::cout << "Invalid name. Try again (\"back\" to go back): " << std::endl;
                        }
                        std::cout << "Negotiate order added." << std::endl;
                        break;
                    }
                    // Don't know what this does / how to implement
                    case reinforcement:
                    {
                        //Add more reinforcements to the player
                        break;
                    }
                    default:
                        break;
                    }
                    p->hasPlayedCard = true;
                    p->hasFinishedIssuingOrders = true;
                }
                break;
            }
            // User wants to end issue order phase
            case 's':
            {

                std::cout << "Human player issue order phase finish." << std::endl;
                p->hasFinishedIssuingOrders = true;
                break;
            }
            // User wants to attack a territory
            // This will create an advance order to a nearby enemy territory
            case 'a':
            {
                std::cout << "Issue attack order." << std::endl;
                nameValid = false;
                validSourceAndTarget = false;
                while (!validSourceAndTarget)
                {
                select_source:
                    //Receives name of source and target of attack and checks them
                    name = "";
                    std::cout << "Human player " << p->name << " territories are: " << std::endl;
                    for (int i = 0; i < p->territories->size(); i++)
                    {
                        std::cout << p->territories->at(i)->name << std::endl;
                    }
                    std::cout << "Select territory to attack from: ";
                    // Get name of source territory
                    name = getName(p);
                    // Checks if player wants to go back to order choosing
                    if (name == "back")
                        goto finish;
                    source = getTerByName(p, name);
                    std::cout << "Attacking territory has " << source->armyCount << " troops." << std::endl;
                    // Get name of target
                    std::cout << "Available territories to attack are: " << std::endl;
                    for (int i = 0; i < source->neighbors.size(); i++)
                    {
                        if (source->neighbors.at(i)->owner != p)
                            std::cout << source->neighbors.at(i)->name << std::endl;
                    }
                    std::cout << "Select territory to attack: ";
                    while (!nameValid) {
                        // If the player wants to go back, program returns to choosing source territory
                        std::cin >> name;
                        if (name == "back")
                            goto select_source;
                        else
                        {
                            // Checks if the target is a neighbor territory and is not owned by issuing player
                            for (Territory* t : source->neighbors)
                            {
                                if (t->name == name && t->owner != p)
                                {
                                    nameValid = true;
                                    target = t;
                                }
                            }
                            if (!nameValid)
                            {
                                std::cout << "Invalid inputs, please try again (\"back\" to go back): " << std::endl;
                            }
                        }
                        if (nameValid)
                        {
                            troops = getTroops(p);
                            if (troops == 0)
                                nameValid = false;
                            else
                                validSourceAndTarget = true;
                        }
                    }
                }
                // Add an advance order and add territory to terToAttack
                p->listOfOrders->add(new advanceOrder(p, source, target, troops));
                terToAttack.push_back(source);
                std::cout << "Attack (advance) order added." << std::endl;
                p->hasFinishedIssuingOrders = true;
                break;
            }
            // User wants to defend a territory
            // This will create an advance order to another owned territory
            case 'd':
            {
                std::cout << "Issue defend order." << std::endl;
                nameValid = false;
                validSourceAndTarget = false;
                while (!nameValid)
                {
                    //Receives name of source and target of attack and checks them
                    while (!validSourceAndTarget)
                    {
                        name = "";
                        std::cout << "Human player " << p->name << " territories are: " << std::endl;
                        for (int i = 0; i < p->territories->size(); i++)
                        {
                            std::cout << p->territories->at(i)->name << std::endl;
                        }
                        std::cout << "Select territory to transfer troops from: ";
                        // Get name of source territory
                        name = getName(p);
                        // Checks if player wants to go back to order choosing
                        if (name == "back")
                            goto finish;
                        source = getTerByName(p, name);
                        // Get name of target
                        std::cout << "Available targets to defend are: " << std::endl;
                        for (int i = 0; i < source->neighbors.size(); i++)
                        {
                            if (source->neighbors.at(i)->owner == p)
                                std::cout << source->neighbors.at(i)->name << std::endl;
                        }
                        std::cout << "Select territory to transfer troops to: ";
                        name = getName(p);
                        target = getTerByName(p, name);
                        // If the player wants to go back, program returns to choosing source territory
                        if (name != "back")
                            // if name == "back" go back to getOption()
                        {
                            //neighbors check
                            for (Territory* t : source->neighbors)
                            {
                                if (t == target)
                                    validSourceAndTarget = true;
                            }
                            if (!validSourceAndTarget)
                            {
                                std::cout << "Selected territory are not neighbors, please try again." << std::endl;
                            }
                        }
                    }
                    // Choose number of troops used in attack
                    troops = getTroops(p);
                    if (troops == 0)
                        validSourceAndTarget = false;
                    else
                        nameValid = true;
                }
                // Add a new advance order and add a territory to terToDefend
                p->listOfOrders->add(new advanceOrder(p, source, target, troops));
                terToDefend.push_back(source);
                std::cout << "Defend (advance) order added." << std::endl;
                p->hasFinishedIssuingOrders = true;
                break;
            }
            default:
            {
                std::cout << "Something went wrong, literally impossible to get here" << std::endl;
                break;
            }
            }
        finish:
            std::cout << "----------------" << std::endl;
        }
    }
}

void HumanPlayerStrategy::resetIssueOrderPhase()
{
    terToAttack.clear();
    terToDefend.clear();
}
std::string HumanPlayerStrategy::describe()
{
    return "This player is user controlled.";
}
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy h)
{
    if (this != &h)
        this->type = h.type;
    return *this;
}
#pragma endregion