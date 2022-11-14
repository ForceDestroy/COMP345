#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>

#include "Map.h"

#pragma region Territory

// Default Constructor - Territory
Territory::Territory() = default;

// Destructor - Territory
Territory::~Territory() = default;

// Constructor - Territory
Territory::Territory(int id, std::string name, int continent)
{
    this->id = id;
    this->name = name;
    this->continent = continent;
    this->armyCount = 0;
    this->visited = false;
}

// Copy constructor - Territory
Territory::Territory(const Territory &t1)
{
    this->id = t1.id;
    this->name = t1.name;
    this->continent = t1.continent;
    this->armyCount = t1.armyCount;
    this->visited = t1.visited;
    for (Territory *t : t1.neighbors)
    {
        auto *copy(new Territory(*t));
        this->neighbors.push_back(copy);
    }
}

// Assignment Operator - Territory
Territory &Territory::operator=(const Territory &t1)
{
    this->id = t1.id;
    this->name = t1.name;
    this->continent = t1.continent;
    this->armyCount = t1.armyCount;
    this->visited = t1.visited;

    return *this;
}

// Stream Insertion Operator - Territory
std::ostream &operator<<(std::ostream &out, const Territory &territory)
{
    out << "{ Id: " << territory.id << ", Name: " << territory.name;
    out << ", Continent: " << territory.continent << ", Army Count: " << territory.armyCount << " }" << std::endl;

    return out;
}

#pragma endregion

#pragma region Continent

// Default constructor - Continent
Continent::Continent() = default;

// Destructor - Continent
Continent::~Continent() = default;

// Constructor - Continent
Continent::Continent(std::string name, int bonus)
{
    this->name = name;
    this->bonus = bonus;
}

// Copy Constructor - Continent
Continent::Continent(const Continent &c1)
{
    this->name = c1.name;
    this->bonus = c1.bonus;
    for (Territory *t : c1.territories)
    {
        auto *copy(new Territory(*t));
        this->territories.push_back(copy);
    }
}

// Assignment Operator - Continent
Continent &Continent::operator=(const Continent &c1)
{
    this->name = c1.name;
    this->bonus = c1.bonus;

    return *this;
}

// Stream Insertion Operator - Continent
std::ostream &operator<<(std::ostream &out, const Continent &continent)
{
    out << "{ Name: " << continent.name << ", Reward: " << continent.bonus << " }" << std::endl;

    return out;
}

#pragma endregion

#pragma region Map

// Default Constructor - Map
Map::Map() = default;

// Destructor - Map
Map::~Map()
{
    for (Continent *c : continents)
    {
        delete c;
    }

    for (Territory *t : territories)
    {
        delete t;
    }
}

// Copy Constructor - Map
Map::Map(const Map &m1)
{
    // Add a copy of all territories
    for (Territory *t : m1.territories)
    {
        auto *copy(new Territory(*t));
        this->territories.push_back(copy);
    }

    // Add a copy of all continents
    for (Continent *c : m1.continents)
    {
        auto *copy(new Continent(*c));
        this->continents.push_back(copy);
    }

    // Add territories to their continents
    int continentId = 1;
    for (Continent *c : m1.continents)
    {
        Continent *cpC = this->continents.at(continentId - 1);
        for (Territory *t : c->territories)
        {
            Territory *cpT = this->territories.at(t->id - 1);
            cpC->territories.push_back(cpT);

            // Add adjacent territories
            for (Territory *adj : t->neighbors)
            {
                Territory *cpAdj = this->territories.at(adj->id - 1);
                cpT->neighbors.push_back(cpAdj);
            }
        }
        continentId++;
    }
}

// Assignment Operator - Map
Map &Map::operator=(const Map &m1)
{
    territories.clear();
    continents.clear();

    // Add a copy of all territories
    for (Territory *t : m1.territories)
    {
        auto *copy(new Territory(*t));
        this->territories.push_back(copy);
    }

    // Add a copy of all continents
    for (Continent *c : m1.continents)
    {
        auto *copy(new Continent(*c));
        this->continents.push_back(copy);
    }

    // Add territories to their continents
    int continentId = 1;
    for (Continent *c : m1.continents)
    {
        Continent *cpC = this->continents.at(continentId - 1);
        for (Territory *t : c->territories)
        {
            Territory *cpT = this->territories.at(t->id - 1);
            cpC->territories.push_back(cpT);

            // Add adjacent territories
            for (Territory *adj : t->neighbors)
            {
                Territory *cpAdj = this->territories.at(adj->id - 1);
                cpT->neighbors.push_back(cpAdj);
            }
        }
        continentId++;
    }

    return *this;
}

// Stream Insertion Operator - Map
std::ostream &operator<<(std::ostream &out, const Map &map)
{
    for (Continent *c : map.continents)
    {
        out << "Continent: " << *c;
        for (Territory *t : c->territories)
        {
            out << *t;
        }
        out << std::endl;
    }

    return out;
}

// Check if all territories in a continent are owned by a single Player
Player* Map::GetContinentOwner(Continent* continent)
{
    Player* owner = continent->territories[0]->owner;
    for (Territory* territory : continent->territories)
    {
        if (territory->owner != owner)
            return NULL;
    }

    return owner;
}

// Visit all territories starting from a given territory
// Used to check if a continent is connected
void Map::VisitContinent(Territory *current, int continent)
{
    for(Territory* neighbor: current->neighbors)
    {
        if(neighbor->continent == continent && !neighbor->visited)
        {
            neighbor->visited = true;
            VisitContinent(neighbor, continent);
        }
    }
}

// Check if a continent is connected
bool Map::CheckContinent(Continent* continent)
{
    for (Territory *territory : continent->territories)
    {
        if (territory->visited)
            territory->visited = false;
        else
            return false;
    }

    return true;
}

// Visit all territories starting from a given territory
// Used to check if the map is connected
void Map::VisitMap(Territory *current)
{
    for (Territory *adj : current->neighbors)
    {
        if (!adj->visited)
        {
            adj->visited = true;
            VisitMap(adj);
        }
    }
}

// Check if the map is connected
bool Map::CheckMap()
{
    for (Territory *territory : territories)
    {
        if (territory->visited)
            territory->visited = false;
        else
            return false;
    }

    return true;
}

// Validates the map is correctly structured
bool Map::Validate()
{
    // If the map has no nodes then it is not a map
    if (territories.empty())
        return false;

    // Visit all adjacency's in the map
    VisitMap(territories.front());

    // Check and reset that all nodes are visited
    if (!CheckMap())
        return false;

    // Check that each continent is a subgraph
    int continentNum = 0;
    for (Continent *cont : continents)
    {
        // Check that each continent has a territory
        if (cont->territories.empty())
            return false;

        // Mark all adjacency's within the continent
        VisitContinent(cont->territories.front(), continentNum);

        // Check and reset that all nodes are visited
        if (!CheckContinent(cont))
            return false;

        continentNum++;
    }

    // Check that each territory belongs to one and only one continent
    continentNum = 0;
    for (Continent *cont : continents)
    {
        // Check that no territories already marked
        for (Territory *t : cont->territories)
            if (t->visited)
                return false;

        // Mark all adjacency's within the continent
        VisitContinent(cont->territories.front(), continentNum);
        continentNum++;
    }

    // Check that all territories have been visited
    if (!CheckMap())
        return false;

    return true;
}

#pragma endregion

#pragma region MapLoader

// Default Constructor - MapLoader
MapLoader::MapLoader()
{
    // Read all maps in the directory
}

// Destructor - MapLoader
MapLoader::~MapLoader() {
    for (Map* m : maps) {
        delete m;
    }
}

// Copy Constructor - MapLoader
MapLoader::MapLoader(const MapLoader &ml1)
{
    // Calls the copy constructor for all maps in the ml1
    for (Map *m : ml1.maps)
    {
        Map *cpM = new Map(*m);
        this->maps.push_back(cpM);
    }
}

// Assignment Operator - MapLoader
MapLoader &MapLoader::operator=(const MapLoader &ml1)
{
    // Calls the copy constructor for all maps in the ml1
    for (Map *m : ml1.maps)
    {
        Map *cpM = new Map(*m);
        this->maps.push_back(cpM);
    }

    return *this;
}

// Loads a map file into an instance of the map class
// Saves the map into the mapLoader if the map is valid
void MapLoader::Load(const std::string &fileName)
{
    // Start map object to populate
    Map *map = new Map();
    bool parsedMap = false;
    
    try {
        size_t lastdot = fileName.find_last_of(".");
        size_t lastslash = fileName.find_last_of("\\");
        if (lastdot == std::string::npos) {
            map->name = fileName;
        }
        else {
            map->name = fileName.substr(lastslash + 1, lastdot);
        }

        

        prepareMapFile(fileName);

        // Open map file
        std::fstream input(fileName);

        // Read the file
        std::string line;

        // Skip the header
        while (std::getline(input, line))
        {
            if (!line.compare("[Continents]"))
            {
                break;
            }
        }

        
        std::vector<std::string> continentNames;

        // Read the continents
        while (std::getline(input, line))
        {
            if (!line.compare("[Territories]"))
            {
                break;
            }

            std::vector<std::string> vec = split(line, '=');
            std::string name = vec[0];
            int bonus = std::stoi(vec[1]);

            Continent* continent = new Continent();
            continent->name = name;
            continent->bonus = bonus;

            map->continents.push_back(continent);
            continentNames.push_back(name);
        }

        std::vector<std::string> territoryNames;
        // Read the territories - No Neighbors
        int territoryId = 0;
        while (std::getline(input, line))
        {
            if (!line.compare(""))
            {
                while (std::getline(input, line))
                {
                    if (!line.compare(""))
                    {
                        break;
                    }
                }
            }

            std::vector<std::string> vec = split(line, ',');
            std::string name = vec[0];
            int id = territoryId;
            int continentId = findIndex(continentNames, vec[3]);

            Territory* territory = new Territory();
            territory->id = territoryId;
            territory->name = name;
            territory->continent = continentId;
            territory->armyCount = 0;

            map->territories.push_back(territory);
            territoryNames.push_back(name);

            territoryId++;
        }

        // Open map file again - for the neighbors
        std::fstream input2(fileName);

        // Skip everything until Territories
        while (std::getline(input2, line))
        {
            if (!line.compare("[Territories]"))
            {
                break;
            }
        }

        // Read the territories - For the Neighbors + Continent
        territoryId = 0;
        while (std::getline(input2, line))
        {
            std::vector<std::string> vec = split(line, ',');
            Territory* cur = map->territories[territoryId];

            Continent* cnt = map->continents[cur->continent];
            cnt->territories.push_back(cur);

            for (int j = 4; j < vec.size(); j++)
            {
                std::string neighbordName = vec[j];
                int neighborId = findIndex(territoryNames, neighbordName);
                cur->neighbors.push_back(map->territories[neighborId]);
            }

            territoryId++;
        }

        parsedMap = true;
    }
    catch (std::invalid_argument e) {
        parsedMap = false;
    }

    if (!parsedMap) {
        std::cout << map->name << "Failed to load: Parser Error" << std::endl;
        delete map;

    }
    else {
        maps.push_back(map);
        std::cout << map->name << " has been loaded" << std::endl;

    }


    //Validate the map before adding
    //if (map->Validate()) {
    //    maps.push_back(map);
    //    std::cout << map->name << " is a valid map" << std::endl;
    //}
    //else {
    //    std::cout << map->name << " is not a valid map: Validation Error" << std::endl;
    //    delete map;
    //}

}

// Helper - Delete all empty lines in the file to create a uniform format
void MapLoader::prepareMapFile(const std::string& FilePath)
{
    std::ifstream in(FilePath);
    std::string line, text;
    while (std::getline(in, line)) {
        if (!(line.empty() || line.find_first_not_of(' ') == std::string::npos))
        {
            std::regex r("\\s+");
            line = std::regex_replace(line, r, "");
            text += line + "\n";
        }
    }
    in.close();
    std::ofstream out(FilePath);
    out << text;
}

// Helper - Split a string into a vector of strings using a delimeter
std::vector<std::string> MapLoader::split(std::string text, char delim)
{
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);
    while (std::getline(ss, line, delim)) {
        vec.push_back(line);
    }
    return vec;
}

// Helper - Find the index of the item in a vector of string
int MapLoader::findIndex(std::vector<std::string> vec, std::string item)
{
    auto it = std::find(vec.begin(), vec.end(), item);
    if (it == vec.end())
    {
        throw std::invalid_argument("ParserError");
    }
    return std::distance(vec.begin(), it);
}


#pragma endregion