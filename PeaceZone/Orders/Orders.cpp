#include "Orders.h"

//Class Orders
#pragma region Orders
//Default constructor
Orders::Orders()
{
    valid = false;
    std::cout << "An order has been created" << std::endl;
}
//Copy constructor
Orders::Orders(const Orders& ord)
{
    valid = ord.valid;
}
//Destructor
Orders::~Orders()
{
    std::cout << "Order has been destroyed" << std::endl;
}
//valid setter
void Orders::setValid(bool isValid)
{
    valid = isValid;
}
//description of order
std::string Orders::describe()
{
    return "Generic Order";
}
//validate the order
void Orders::validate()
{
    setValid(true);
    std::cout << "Default validation statement" << std::endl;
}
//execute the order
void Orders::execute()
{
    validate();
            if (valid)
            {
                std::cout << "Blank order execute" << std::endl;
                describe();
            }
            else
            {
                std::cout << "This order is not valid." << std::endl;
            }
}
//Overloaded operators
Orders& Orders::operator=(const Orders &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, Orders &orders)
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
    std::cout << "Deploy order has been created" << std::endl;
}
//Copy constructor
deployOrder::deployOrder(const deployOrder& ord)
{
    valid = ord.valid;
}
//Destructor
deployOrder::~deployOrder()
{
    std::cout << "Deploy order has been destroyed" << std::endl;
}

//description of order
std::string deployOrder::describe()
{
    return "Deploy Order";
}
//validate the order
void deployOrder::validate()
{
    setValid(true);
    std::cout << "Deploy order validation statement" << std::endl;
}
//execute the order
void deployOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Deploy order execute" << std::endl;
        describe();
    }
    else
    {
        std::cout << "This order is not valid." << std::endl;
    }
}
//Overloaded operators
deployOrder& deployOrder::operator=(const deployOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, deployOrder &orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class advanceOrder
#pragma region advanceOrder
//Default constructor
advanceOrder::advanceOrder()
{
    std::cout << "Advance order has been created" << std::endl;
}
//Copy constructor
advanceOrder::advanceOrder(const advanceOrder& ord)
{
    valid = ord.valid;
}
//Destructor
advanceOrder::~advanceOrder()
{
    std::cout << "Advance order has been destroyed" << std::endl;
}

//description of order
std::string advanceOrder::describe()
{
    return "Advance Order";
}
//validate the order
void advanceOrder::validate()
{
    setValid(true);
    std::cout << "Advance order is validated." << std::endl;
}
//execute the order
void advanceOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Advance order is executed" << std::endl;
        describe();
    }
    else
    {
        std::cout << "This order is not valid." << std::endl;
    }
}
//Overloaded operators
advanceOrder& advanceOrder::operator=(const advanceOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, advanceOrder &orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class bombOrder
#pragma region bombOrder
//Default constructor
bombOrder::bombOrder()
{
    std::cout << "Bomb order has been created" << std::endl;
}
//Copy constructor
bombOrder::bombOrder(const bombOrder& ord)
{
    valid = ord.valid;
}
//Destructor
bombOrder::~bombOrder()
{
    std::cout << "Bomb order has been destroyed" << std::endl;
}
//description of order
std::string bombOrder::describe()
{
    return "Bomb Order";
}
//validate the order
void bombOrder::validate()
{
    setValid(true);
    std::cout << "Bomb order is validated." << std::endl;
}
//execute the order
void bombOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Bomb order is executed" << std::endl;
        describe();
    }
    else
    {
        std::cout << "This bomb order is not valid." << std::endl;
    }
}
//Overloaded operators
bombOrder& bombOrder::operator=(const bombOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, bombOrder &orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class blockadeOrder
#pragma region blockadeOrder
//Default constructor
blockadeOrder::blockadeOrder()
{
    std::cout << "Blockade order has been created" << std::endl;
}
//Copy constructor
blockadeOrder::blockadeOrder(const blockadeOrder& ord)
{
    valid = ord.valid;
}
//Destructor
blockadeOrder::~blockadeOrder()
{
    std::cout << "Blockade order has been destroyed" << std::endl;
}
//description of order
std::string blockadeOrder::describe()
{
    return "Blockade Order";
}
//validate the order
void blockadeOrder::validate()
{
    setValid(true);
    std::cout << "Blockade order is validated." << std::endl;
}
//execute the order
void blockadeOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Blockade order is executed" << std::endl;
        describe();
    }
    else
    {
        std::cout << "This blockade order is not valid." << std::endl;
    }
}
//Overloaded operators
blockadeOrder& blockadeOrder::operator=(const blockadeOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, blockadeOrder &orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class airliftOrder
#pragma region airliftOrder
//Default constructor
airliftOrder::airliftOrder()
{
    std::cout << "Airlift order has been created" << std::endl;
}
//Copy constructor
airliftOrder::airliftOrder(const airliftOrder& ord)
{
    valid = ord.valid;
}
//Destructor
airliftOrder::~airliftOrder()
{
    std::cout << "Airlift order has been destroyed" << std::endl;
}
//description of order
std::string airliftOrder::describe()
{
    return "Airlift Order";
}
//validate the order
void airliftOrder::validate()
{
    setValid(true);
    std::cout << "Airlift order is validated." << std::endl;
}
//execute the order
void airliftOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Airlift order is executed" << std::endl;
        describe();
    }
    else
    {
        std::cout << "This airlift order is not valid." << std::endl;
    }
}
//Overloaded operators
airliftOrder& airliftOrder::operator=(const airliftOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, airliftOrder &orders)
{
    out << orders.describe() << std::endl;
    return out;
}
#pragma endregion

//Class negotiateOrder
#pragma region negotiateOrder
//Default constructor
negotiateOrder::negotiateOrder()
{
    std::cout << "Negotiate order has been created" << std::endl;
}
//Copy constructor
negotiateOrder::negotiateOrder(const negotiateOrder& ord)
{
    valid = ord.valid;
}
//Destructor
negotiateOrder::~negotiateOrder()
{
    std::cout << "Negotiate order has been destroyed" << std::endl;
}
//description of order
std::string negotiateOrder::describe()
{
   return "Negotiate Order";
}
//validate the order
void negotiateOrder::validate()
{
    setValid(true);
    std::cout << "Negotiate order is validated." << std::endl;
}
//execute the order
void negotiateOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Negotiate order is executed" << std::endl;
        describe();
    }
    else
    {
        std::cout << "This negotiate order is not valid." << std::endl;
    }
}
//Overloaded operators
negotiateOrder& negotiateOrder::operator=(const negotiateOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, negotiateOrder& orders)
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
}
//Destructor
OrdersList::~OrdersList()
{
    for ( Orders* o : *ordersList)
    {
        delete o;
    }
    delete ordersList;
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
            Orders *temp = ordersList->at(i);
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
OrdersList& OrdersList::operator=(const OrdersList &ord)
{
    ordersList = new std::vector<Orders*>();
    for (int i = 0; i < ord.ordersList->size(); i++)
    {
        ordersList->push_back(ord.ordersList->at(i));
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out, const OrdersList &orders)
{
    out << "The list of orders:" << std::endl;
    for(Orders* o: *orders.ordersList)
    {
        out << "Order: "<< *o;
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
#pragma endregion