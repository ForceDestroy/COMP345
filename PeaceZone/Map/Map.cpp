#include <iostream>
#include <list>
#include <memory>
#include "Territory.h"

class Map
{
private:

public:
    // Constructors + Destructors
    Map()
    {

    }

    Map(Map& other)
    {

    }

    ~Map()
    {
        std::cout << "Map has been destroyed." << std::endl;
    }


};