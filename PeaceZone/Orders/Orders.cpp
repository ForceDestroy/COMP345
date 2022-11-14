#include "Orders.h"

//Class Orders
#pragma region Orders
//Default constructor
Orders::Orders()
{
    player = NULL;
    valid = false;
    std::cout << "An order has been created." << std::endl;
}
//Parameterized constructor
Orders::Orders(Player* player)
{
    this->player = player;
    valid = false;
    std::cout << "An order has been created." << std::endl;
}
//Copy constructor
Orders::Orders(const Orders& ord)
{
    player = ord.player;
    valid = ord.valid;
    std::cout << "An order has been created." << std::endl;
}
//Destructor
Orders::~Orders()
{
    std::cout << "Order has been destroyed." << std::endl;
}
//valid setter
void Orders::setValid(bool isValid)
{
    this->valid = isValid;
}
//player setter
void Orders::setPlayer(Player* player)
{
    this->player = player;
}
//description of order
std::string Orders::describe()
{
    return "Default Order";
}
//validate the order
void Orders::validate()
{
    setValid(true);
    std::cout << "Default validation statement." << std::endl;
}
//execute the order
void Orders::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Default order execute." << std::endl;
        describe();
    }
}
//Overloaded operators
Orders& Orders::operator=(const Orders& ord)
{
    this->player = ord.player;
    this->valid = ord.valid;
    return *this;
}
//Assignment operator
std::ostream& operator<<(std::ostream& out, Orders& orders)
{

    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class deployOrder
#pragma region deployOrder
//Default constructor
deployOrder::deployOrder()
{
    Orders();
    this->target = NULL;
    this->troopNum = 0;
    std::cout << "Deploy order has been created." << std::endl;
}
//Parmaterized constructor
deployOrder::deployOrder(Player* player, Territory* target, const int troopNum):Orders(player)
{
    this->target = target;
    this->troopNum = troopNum;
    std::cout << "Deploy order has been created." << std::endl;
}
//Copy constructor
deployOrder::deployOrder(const deployOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->target = ord.target;
    this->troopNum = ord.troopNum;
    std::cout << "Deploy order has been created." << std::endl;
}
//Destructor
deployOrder::~deployOrder()
{
    std::cout << "Deploy order has been destroyed." << std::endl;
}

//description of order
std::string deployOrder::describe()
{
    return "Deploy Order moves troops from reserves to territory";
}
//validate the order
void deployOrder::validate()
{
    if (target->owner == this->player && this->player->reinforcementPool >= this->troopNum)
    {
        setValid(true);
        std::cout << "Deploy order is valid." << std::endl;
    }
    else
    {
        setValid(false);
        std::cout << "Deploy order is not valid." << std::endl;
    }
}
//execute the order
void deployOrder::execute()
{
    validate();
    if (valid)
    {
        describe();
        std::cout << "Deploy order is executed." << std::endl;
        target->armyCount += troopNum;
    }
    else
    {
        std::cout << "Deploy order is not executed." << std::endl;
    }
}
//target territory setter
void deployOrder::setTarget(Territory* target)
{
    this->target = target;
}
//Number of troops setter
void deployOrder::setTroops(const int troopNum)
{
    this->troopNum = troopNum;
}
//Overloaded operators
deployOrder& deployOrder::operator=(const deployOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->target = ord.target;
    this->troopNum = ord.troopNum;
    return *this;
}
//assigment operator
std::ostream& operator<<(std::ostream& out, deployOrder& orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class advanceOrder
#pragma region advanceOrder
//Default constructor
advanceOrder::advanceOrder():Orders()
{
    this->source = NULL;
    this->target = NULL;
    this->troopNum = 0;
    std::cout << "Advance order has been created." << std::endl;
}
//Parameterized constructor
advanceOrder::advanceOrder(Player* player, Territory* source, Territory* target, const int troopNum):Orders(player)
{
    this->source = source;
    this->target = target;
    this->troopNum = troopNum;
    std::cout << "Advance order has been created." << std::endl;
}
//Copy constructor
advanceOrder::advanceOrder(const advanceOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->source = ord.source;
    this->target = ord.target;
    this->troopNum = ord.troopNum;
    std::cout << "Advance order has been created." << std::endl;
}
//Destructor
advanceOrder::~advanceOrder()
{
    std::cout << "Advance order has been destroyed." << std::endl;
}

//description of order
std::string advanceOrder::describe()
{
    return "Advance Order moves troop from 1 owned territory to another or attacks enemy territory";
}
//checks if the source and target territory is adjacent
bool advanceOrder::isNeighbor()
{
    for (Territory* t : this->source->neighbors)
    {
        if (t->id == target->id)
            return true;
    }
    return false;
}
//validate the order
void advanceOrder::validate()
{
    if (this->source->id != this->target->id && source->owner == player && isNeighbor() && source->armyCount > 1 && source->armyCount > troopNum)
    {
        setValid(true);
        std::cout << "Advance order is valid." << std::endl;
    }
    else
    {
        std::cout << "Advance order is not valid." << std::endl;
    }
}
//execute the order
void advanceOrder::execute()
{
    validate();
    if (valid)
    {
        describe();
        if (target->owner == player)
        {
            std::cout << "Advance order is executed." << std::endl;
            source->armyCount -= troopNum;
            target->armyCount += troopNum;
        }
        else if (this->player->truce(this->target->owner))
        {
            std::cout << "Attack invalid because players under truce" << std::endl;
        }
        else
        {
            std::cout << "Advance order is executed." << std::endl;
            simulateAttack();
        }
    }
    else
    {
        std::cout << "Advance order is not executed." << std::endl;
    }
}
//simulates attacks between 2 territories
void advanceOrder::simulateAttack()
{
    srand(time(0));
    int randNum;
    int attackersKilled = 0, defendersKilled = 0;
    for (int i = 0; i < troopNum; i++)
    {
        if (rand() % 10 > 3) // This represents a 60% chance to kill a defender 
            defendersKilled++;
    }
    for (int k = 0; k < target->armyCount; k++)
    {
        if (rand() % 10 > 2) // This represents a 70% chance to kill an attacker
            attackersKilled++;
    }
    if (defendersKilled >= target->armyCount)
    {
        if (attackersKilled >= troopNum) // If all attackers and defenders die then defenders win with 1 remaining troop
        {
            target->armyCount = 1;
            this->troopNum = 0;
            std::cout << "Attack failed." << std::endl;
        }
        else
        {
            this->target->owner = this->player;
            this->target->armyCount = this->troopNum - attackersKilled;
            if (!this->player->hasConqTerritory)
            {
                this->player->hasConqTerritory = true;
            }
            std::cout << "Attack succeeded." << std::endl;
        }
    }
    else
    {
        this->troopNum = 0;
        this->target->armyCount -= defendersKilled;
        std::cout << "Attack failed." << std::endl;
    }
}
//source territory setter
void advanceOrder::setSource(Territory* source)
{
    this->source = source;
}
//target territory setter
void advanceOrder::setTarget(Territory* target)
{
    this->target = target;
}
//number of troops setter
void advanceOrder::setTroops(const int troopNum)
{
    this->troopNum = troopNum;
}
//Overloaded operators
advanceOrder& advanceOrder::operator=(const advanceOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->source = ord.source;
    this->target = ord.target;
    this->troopNum = ord.troopNum;
    return *this;
}
//assignment operator
std::ostream& operator<<(std::ostream& out, advanceOrder& orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class bombOrder
#pragma region bombOrder
//Default constructor
bombOrder::bombOrder():Orders()
{
    this->target = NULL;
    std::cout << "Bomb order has been created." << std::endl;
}
//Copy constructor
bombOrder::bombOrder(const bombOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->target = ord.target;
    std::cout << "Bomb order has been destroyed." << std::endl;
}
//Parameterized constructor
bombOrder::bombOrder(Player* player, Territory* target):Orders(player)
{
    this->target = target;
    std::cout << "Bomb order has been destroyed." << std::endl;
}
//Destructor
bombOrder::~bombOrder()
{
    std::cout << "Bomb order has been destroyed." << std::endl;
}
//description of order
bool bombOrder::isAdjacent()
{
    for (Territory* t : this->target->neighbors)
    {
        if (t->owner == player)
            return true;
    }
    return false;
}
std::string bombOrder::describe()
{
    return "Bomb Order reduces number of troops in a territory by half, rounding down.";
}
//validate the order
void bombOrder::validate()
{
    if (this->target->owner != player && isAdjacent())
    {
        setValid(true);
        std::cout << "Bomb order is valid." << std::endl;
    }
    else
    {
        setValid(false);
        std::cout << "Bomb order is not valid." << std::endl;
    }
}
//execute the order
void bombOrder::execute()
{
    validate();
    if (valid)
    {
        describe();
        std::cout << "Bomb order is executed." << std::endl;
        this->target->armyCount /= 2;
    }
    else
    {
        std::cout << "Bomb order is not executed." << std::endl;
    }
}
//Target territory setter
void bombOrder::setTarget(Territory* target)
{
    this->target = target;
}
//Overloaded operators
bombOrder& bombOrder::operator=(const bombOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->target = ord.target;
    return *this;
}
//Assignment operator
std::ostream& operator<<(std::ostream& out, bombOrder& orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class blockadeOrder
#pragma region blockadeOrder
//Default constructor
blockadeOrder::blockadeOrder():Orders()
{
    this->target = NULL;
    std::cout << "Blockade order has been created." << std::endl;
}
//Copy constructor
blockadeOrder::blockadeOrder(const blockadeOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->target = ord.target;
    std::cout << "Blockade order has been created." << std::endl;
}
//Parameterized constructor
blockadeOrder::blockadeOrder(Player* player, Territory* target):Orders(player)
{
    this->target = target;
    std::cout << "Blockade order has been created." << std::endl;
}
//Destructor
blockadeOrder::~blockadeOrder()
{
    std::cout << "Blockade order has been destroyed." << std::endl;
}
//description of order
std::string blockadeOrder::describe()
{
    return "The blockade order doubles the troops on a territory but makes it neutral.";
}
//validate the order
void blockadeOrder::validate()
{
    if (target->owner == player)
    {
        setValid(true);
        std::cout << "Blockade order is valid." << std::endl;
    }
    else
    {
        setValid(false);
        std::cout << "Blockdade order is not valid." << std::endl;
    }
}
//execute the order
void blockadeOrder::execute()
{
    validate();
    if (valid)
    {
        describe();
        std::cout << "Blockade order is executed." << std::endl;
        this->target->armyCount *= 2;
        this->target->owner = NULL;
    }
    else
    {
        std::cout << "Blockade order is not executed." << std::endl;
    }
}
//Target territory setter
void blockadeOrder::setTarget(Territory* target)
{
    this->target = target;
}
//Overloaded operators
blockadeOrder& blockadeOrder::operator=(const blockadeOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->target = ord.target;
    return *this;
}
//Assignment operator
std::ostream& operator<<(std::ostream& out, blockadeOrder& orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class airliftOrder
#pragma region airliftOrder
//Default constructor
airliftOrder::airliftOrder():Orders()
{
    std::cout << "Airlift order has been created." << std::endl;
}
//Copy constructor
airliftOrder::airliftOrder(const airliftOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->source = ord.source;
    this->target = ord.target;
    this->troopNum = ord.troopNum;
    std::cout << "Airlift order has been created." << std::endl;
}
airliftOrder::airliftOrder(Player* player, Territory* source, Territory* target, const int troopNum) :Orders(player)
{
    this->source = source;
    this->target = target;
    this->troopNum = troopNum;
    std::cout << "Airlift order has been created." << std::endl;
}
//Destructor
airliftOrder::~airliftOrder()
{
    std::cout << "Airlift order has been destroyed." << std::endl;
}
//description of order
std::string airliftOrder::describe()
{
    return "The airlift order can move troops between non-adjacent territories.";
}
//validate the order
void airliftOrder::validate()
{
    if (this->target->id != this->source->id && this->target->owner == this->player && this->source->owner == player && this->source->armyCount > 1 && this->source->armyCount > this->troopNum)
    {
        setValid(true);
        std::cout << "Airlift order is valid." << std::endl;
    }
    else
    {
        setValid(false);
        std::cout << "Airlift order is not valid." << std::endl;
    }
}
//execute the order
void airliftOrder::execute()
{
    validate();
    if (valid)
    {
        describe();
        std::cout << "Airlift order is executed." << std::endl;
        this->source->armyCount -= this->troopNum;
        this->target->armyCount += this->troopNum;
    }
    else
    {
        std::cout << "Airlift order is not executed." << std::endl;
    }
}
//Source territory setter
void airliftOrder::setSource(Territory* source)
{
    this->source = source;
}
//Target territory setter
void airliftOrder::setTarget(Territory* target)
{
    this->target = target;
}
//Number of troops setter
void airliftOrder::setTroops(const int troopNum)
{
    this->troopNum = troopNum;
}
//Overloaded operators
airliftOrder& airliftOrder::operator=(const airliftOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->source = ord.source;
    this->target = ord.target;
    this->troopNum = ord.troopNum;
    return *this;
}
//Assignment operator
std::ostream& operator<<(std::ostream& out, airliftOrder& orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class negotiateOrder
#pragma region negotiateOrder
//Default constructor
negotiateOrder::negotiateOrder() :Orders()
{
    std::cout << "Negotiate order has been created." << std::endl;
}
//Copy constructor
negotiateOrder::negotiateOrder(const negotiateOrder& ord)
{
    this->valid = ord.valid;
    this->target = ord.target;
    std::cout << "Negotiate order has been created." << std::endl;
}
//Parameterized constructor
negotiateOrder::negotiateOrder(Player* player, Player* target) :Orders(player)
{
    this->target = target;
    std::cout << "Negotiate order has been created." << std::endl;
}
//Destructor
negotiateOrder::~negotiateOrder()
{
    std::cout << "Negotiate order has been destroyed." << std::endl;
}
//description of order
std::string negotiateOrder::describe()
{
    return "The negotiate order prevents the target player from attacking you this turn.";
}
//validate the order
void negotiateOrder::validate()
{
    if (this->player != this->target)
    {
        setValid(true);
        std::cout << "Negotiate order is valid." << std::endl;
    }
    else
    {
        setValid(false);
        std::cout << "Negotiate order is not valid." << std::endl;
    }
}
//execute the order
void negotiateOrder::execute()
{
    validate();
    if (valid)
    {
        describe();
        std::cout << "Negotiate order is executed." << std::endl;
        this->player->addNegotiateList(this->target);
    }
    else
    {
        std::cout << "Negotiate order is not executed." << std::endl;
    }
}
//Target player setter
void negotiateOrder::setTarget(Player* player)
{
    this->target = target;
}
//Overloaded operators
negotiateOrder& negotiateOrder::operator=(const negotiateOrder& ord)
{
    this->valid = ord.valid;
    this->player = ord.player;
    this->target = ord.target;
    return *this;
}
//Assignment operator
std::ostream& operator<<(std::ostream& out, negotiateOrder& orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class OrdersList
#pragma region OrdersList
//Default constructor
OrdersList::OrdersList()
{
    ordersList = new std::vector<Orders*>();
    std::cout << "An order list has been created." << std::endl;
}
//Copy constructor
OrdersList::OrdersList(const OrdersList& ord)
{
    ordersList = new std::vector<Orders*>();
    for (int i = 0; i < ord.ordersList->size(); i++)
    {
        ordersList->push_back(ord.ordersList->at(i));
    }
    std::cout << "An order list has been created." << std::endl;
}
//Destructor
OrdersList::~OrdersList()
{
    for (Orders* o : *ordersList)
    {
        delete o;
    }
    delete ordersList;
    std::cout << "Order list has been destroyed." << std::endl;
}
//add an order to the list
void OrdersList::add(Orders* order)
{
    ordersList->push_back(order);
    std::cout << "An order has been added" << std::endl;
}
//remove an order from the list
void OrdersList::remove(Orders* order)
{
    for (int i = 0; i < ordersList->size(); i++)
    {
        if (ordersList->at(i) == order)
        {
            Orders* temp = ordersList->at(i);
            ordersList->erase(ordersList->begin() + i);
            delete temp;
            std::cout << "An order has been removed" << std::endl;
        }
    }
}
//move an order to the front of the list
void OrdersList::move(Orders* order, int position)
{
    std::vector<Orders*>::iterator itr1 = ordersList->begin();
    int index = findOrderIndex(*ordersList, order);
    std::advance(itr1, position);
    ordersList->emplace(itr1, order);
    ordersList->erase(ordersList->begin() + index + 1);
    std::cout << "The order has been moved" << std::endl;
}
//Overloaded operators
OrdersList& OrdersList::operator=(const OrdersList& ord)
{
    ordersList = new std::vector<Orders*>();
    for (int i = 0; i < ord.ordersList->size(); i++)
    {
        ordersList->push_back(ord.ordersList->at(i));
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const OrdersList& orders)
{
    out << "The list of orders:" << std::endl;
    for (Orders* o : *orders.ordersList)
    {
        out << "Order: " << *o;
    }
    return out;
}
Orders* OrdersList::operator [](int ItemKey) {
    return (*ordersList)[ItemKey];
}

// Helper - Find the index of the item in a vector of string
int OrdersList::findOrderIndex(std::vector<Orders*> vec, Orders* item)
{
    auto it = std::find(vec.begin(), vec.end(), item);
    if (it == vec.end())
    {
        throw std::invalid_argument("CannotFindItem");
    }
    return std::distance(vec.begin(), it);
}

int OrdersList::getSize() {
    return ordersList->size();
}
#pragma endregion