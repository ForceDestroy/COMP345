#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

class Player;

class Territory
{
public:
    // Data Members
    int id;
    std::string name;
    Player* owner;
    int continent;
    int armyCount;
    std::vector<Territory *> neighbors;
    bool visited; // Used for Validation

    // Constructors
    Territory();
    ~Territory();
    Territory(int id, std::string name, int continent);
    Territory(const Territory &t1);

    // Methods
    Territory &operator=(const Territory &);
    friend std::ostream &operator<<(std::ostream &out, const Territory &territory);
};

class Continent
{
public:
    // Data Members
    std::string name;
    int bonus;
    std::vector<Territory *> territories;

    // Constructors
    Continent();
    ~Continent();
    Continent(std::string name, int bonus);
    Continent(const Continent &c1);

    // Methods
    Continent &operator=(const Continent &);
    friend std::ostream &operator<<(std::ostream &out, const Continent &continent);
};

class Map
{
public:
    // Data Members
    std::string name;
    std::vector<Continent *> continents;
    std::vector<Territory *> territories;

    // Constructors
    Map();
    ~Map();
    Map(const Map &m1);

    // Methods
    Map &operator=(const Map &);
    friend std::ostream &operator<<(std::ostream &out, const Map &map);
    Player* GetContinentOwner(Continent* continent);

    bool Validate();

private:
    // Methods for Validation
    void VisitContinent(Territory *current, int continent);
    bool CheckContinent(Continent *continent);
    void VisitMap(Territory *current);
    bool CheckMap();
};


class MapLoader
{
public:
    // Data Members
    std::vector<Map*> maps;

    // Constructors
    MapLoader();
    ~MapLoader();
    MapLoader(const MapLoader& ml1);

    // Methods
    MapLoader& operator=(const MapLoader&);
    friend std::ostream& operator<<(std::ostream& out, const MapLoader& mapLoader);

    void Load(const std::string& fileName);

private:
    void prepareMapFile(const std::string& filePath);
    std::vector<std::string> split(std::string text, char delim);
    int findIndex(std::vector<std::string> vec, std::string item);
};