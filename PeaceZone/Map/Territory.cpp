#include <iostream>
#include <list>
#include <memory>

// Represents a single territory on the map
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
		// Constructors + Destructors
		Territory(std::string name, std::string continent)
		{
			name = name;
			continent = continent;
			std::initializer_list<std::shared_ptr<Territory>> adjacentTerritories = {};

			armies = 0;
			owner = -1;

			std::cout << "Territory " << name << " has been created." << std::endl;
		}

		Territory(Territory& other)
		{
			name = other.name;
			continent = other.continent;
			adjacentTerritories = other.adjacentTerritories;

			armies = other.armies;
			owner = other.owner;

			std::cout << "Territory " << name << " has been copied." << std::endl;
		}

		~Territory()
		{
			std::cout << "Territory " << name << " has been destroyed." << std::endl;
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

		std::string getContinent()
		{
			return continent;
		}

		void setContinent(std::string newContinent)
		{
			continent = newContinent;
		}

		std::list<std::shared_ptr<Territory>> getAdjacentTerritories()
		{
			return adjacentTerritories;
		}

		void addAdjacentTerritory(std::shared_ptr<Territory> adjacentTerritory)
		{
			adjacentTerritories.push_back(adjacentTerritory);
		}

		void removeAdjacentTerritory(std::shared_ptr<Territory> adjacentTerritory)
		{
			adjacentTerritories.remove(adjacentTerritory);
		}

		int getOwner()
		{
			return owner;
		}

		void setOwner(int newOwner)
		{
			owner = newOwner;
		}

		int getArmies()
		{
			return armies;
		}

		void setArmies(int newArmies)
		{
			armies = newArmies;
		}

		// Stream Insertion Operator
		friend std::ostream& operator<<(std::ostream& os, const Territory& territory)
		{
			os << "Territory " << territory.name << " is owned by player " << territory.owner << " and has " << territory.armies << " armies." << std::endl;
			return os;
		}

		// Public Methods
		std::shared_ptr<Territory> findAdjacentTerritory(std::list<std::shared_ptr<Territory>> allTerritories, std::string name)
		{
			for (std::shared_ptr<Territory> territory : allTerritories)
			{
				if (territory->getName() == name)
				{
					return territory;
				}
			}
			return nullptr;
		}
};