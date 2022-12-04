
//need to write test function
//need to account for a neutral player in game enginer

#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <variant>


#include "../GameEngine/GameEngine.h"
#include "../Player/Player.h"
#include "../Player/PlayerStrategies.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "Orders.fwd.h"
#include "../LoggingObserver/LoggingObserver.h"

#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

class Orders : public ILoggable, public Subject
{
protected:
    bool valid = false;
    // player variable stores the player who issued the order
    Player* player;
public:
    // Constructors
    Orders();
    Orders(Player* player);
    Orders(const Orders& ord);
    virtual ~Orders();

    // Methods
    virtual void execute();
    virtual void validate();
    virtual std::string describe();
    void setValid(bool isValid);
    void setPlayer(Player* player);
    Orders& operator=(const Orders& ord);
    friend std::ostream& operator<<(std::ostream& out, const Orders& orders);

    std::string stringToLog() override;
};

// execute method for subclases not required now and will be added later
// deploy checks for valid: selected player, selected territory, target territory (owned by selected player), troop number (available reserves)
class deployOrder : public Orders
{
private:
    //target variable stores the territory the troops is to be deployed to
    Territory* target;
    int troopNum;
public:
    // Constructors
    deployOrder();
    deployOrder(Player* player, Territory* target, const int troopNum);
    deployOrder(const deployOrder& ord);
    ~deployOrder();

    // Methods
    void execute() override;
    void validate() override;
    std::string describe() override;
    void setTarget(Territory* target);
    void setTroops(const int troopNum);
    deployOrder& operator=(const deployOrder& ord);
    friend std::ostream& operator<<(std::ostream& out, const deployOrder& orders);
};

// advance checks for valid: selected player, selected territory, target territory, troop number
class advanceOrder : public Orders
{
private:
    //source variable stores the territory the troops comes from
    Territory* source;
    Territory* target;
    int troopNum;
public:
    // Constructors
    advanceOrder();
    advanceOrder(Player* player, Territory* source, Territory* target, const int troopNum);
    advanceOrder(const advanceOrder& ord);
    ~advanceOrder();

    // Methods
    bool isNeighbor();
    void execute();
    void validate();
    void simulateAttack();
    std::string describe();
    void setSource(Territory* source);
    void setTarget(Territory* target);
    void setTroops(const int troopNum);
    advanceOrder& operator=(const advanceOrder& ord);
    friend std::ostream& operator<<(std::ostream& out, const advanceOrder& orders);
};
// bomb checks for valid: selected player, target territory (adjacent to owned territory), card availability
class bombOrder : public Orders
{
private:
    Territory* target;
public:
    // Constructors
    bombOrder();
    bombOrder(Player* player, Territory* target);
    bombOrder(const bombOrder& ord);
    ~bombOrder();

    // Methods
    bool isAdjacent();
    void execute();
    void validate();
    std::string describe();
    void setTarget(Territory* target);
    bombOrder& operator=(const bombOrder& ord);
    friend std::ostream& operator<<(std::ostream& out, const bombOrder& orders);
};

// blockade checks for: selected territory, card availability
class blockadeOrder : public Orders
{
private:
    Territory* target;
public:
    // Constructors
    blockadeOrder();
    blockadeOrder(Player* player, Territory* target);
    blockadeOrder(const blockadeOrder& ord);
    ~blockadeOrder();

    // Methods
    void execute();
    void validate();
    std::string describe();
    void setTarget(Territory* target);
    blockadeOrder& operator=(const blockadeOrder& ord);
    friend std::ostream& operator<<(std::ostream& out, const blockadeOrder& orders);
};

// airlift order checks for valid: selected player, selected territory, target territory, troop number, card availability
class airliftOrder : public Orders
{
private:
    Territory* source;
    Territory* target;
    int troopNum;
public:
    // Constructors
    airliftOrder();
    airliftOrder(Player* player, Territory* source, Territory* target, const int troopNum);
    airliftOrder(const airliftOrder& ord);
    ~airliftOrder();

    // Methods
    void execute();
    void validate();
    std::string describe();
    void setSource(Territory* source);
    void setTarget(Territory* target);
    void setTroops(const int troopNum);
    airliftOrder& operator=(const airliftOrder& ord);
    friend std::ostream& operator<<(std::ostream& out, const airliftOrder& orders);
};

// negotiate order checks for valid: selected player, target player
class negotiateOrder : public Orders
{
private:
    Player* target;
public:
    // Constructors
    negotiateOrder();
    negotiateOrder(Player* player, Player* target);
    negotiateOrder(const negotiateOrder& ord);
    ~negotiateOrder();

    // Methods
    void execute();
    void validate();
    std::string describe();
    void setTarget(Player* player);
    negotiateOrder& operator=(const negotiateOrder& ord);
    friend std::ostream& operator<<(std::ostream& out, const negotiateOrder& orders);
};

// OrdersList class
class OrdersList : public ILoggable, public Subject
{
public:
    std::vector<Orders*>* ordersList;
    // Constructors
    OrdersList();
    OrdersList(const OrdersList& ord);
    ~OrdersList();

    // Methods
    void add(Orders* order);
    void remove(Orders* order);
    void move(Orders* order, int position);
    int getSize();

    // Operators
    OrdersList& operator=(const OrdersList& ord);
    friend std::ostream& operator<<(std::ostream& out, const OrdersList& orders);
    Orders* operator[](int itemKey);

    // Helpers
    int findOrderIndex(std::vector<Orders*> vec, Orders* item);

    std::string stringToLog() override;
};