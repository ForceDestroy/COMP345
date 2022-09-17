#include <iostream>
#include <list>
#include <memory>
#include "Territory.h"

class Continent
{
private:
    // Continent Identifier Parameters
    std::string name;
    int value;
    std::list<std::shared_ptr<Territory>> territories;

public:
    // Constructors + Destructors
    Continent(std::string name, int value)
    {
        name = name;
        value = value;
        std::initializer_list<std::shared_ptr<Territory>> territories = {};

        std::cout << "Continent " << name << " has been created." << std::endl;
    }

    Continent(Continent& other)
    {
        name = other.name;
        value = other.value;
        territories = other.territories;

        std::cout << "Continent " << name << " has been copied." << std::endl;
    }

    ~Continent()
    {
        std::cout << "Continent " << name << " has been destroyed." << std::endl;
    }

    // Assignment Operators
    std::string getName()
    {
        return name;
    }

    void setName(std::string newName)
    {
        name = newName;
    }

    int getValue()
    {
        return value;
    }

    void setValue(int newValue)
    {
        value = newValue;
    }

    std::list<std::shared_ptr<Territory>> getTerritories()
    {
        return territories;
    }

    void addTerritory(std::shared_ptr<Territory> newTerritory)
    {
        territories.push_back(newTerritory);
    }

    void removeTerritory(std::shared_ptr<Territory> oldTerritory)
    {
        territories.remove(oldTerritory);
    }

    // Stream Insertion Operator
    friend std::ostream &operator<<(std::ostream &os, const Continent &continent)
    {
        os << "Continent " << continent.name << " has value " << continent.value << " and contains territories: " << std::endl;
        for (std::shared_ptr<Territory> territory : continent.territories)
        {
            os << *territory << std::endl;
        }
        return os;
    }

    // Public Methods
};