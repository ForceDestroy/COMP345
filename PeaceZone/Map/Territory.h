#include <iostream>
#include <list>
#include <memory>

class Territory
{
private:
    // Territory Identifier Parameters
    std::string name;
    std::string continent;
    std::list<std::shared_ptr<Territory>> adjacentTerritories;

    // Gamestate Parameters
    int owner;
    int armies;

public:
    // Assignment Operators
    std::string getName();
    void setName(std::string newName);
    std::string getContinent();
    void setContinent(std::string newContinent);
    std::list<std::shared_ptr<Territory>> getAdjacentTerritories();
    void addAdjacentTerritory(std::shared_ptr<Territory> adjacentTerritory);
    void removeAdjacentTerritory(std::shared_ptr<Territory> adjacentTerritory);
    int getOwner();
    void setOwner(int newOwner);
    int getArmies();
    void setArmies(int newArmies);

    // Stream Insertion Operator
    friend std::ostream &operator<<(std::ostream &os, const Territory &territory);

    // Public Methods
    std::shared_ptr<Territory> findAdjacentTerritory(std::list<Territory> allTerritories, std::string name);
};