#include "Orders.h"

Orders::Orders()
{
    valid = false;
    std::cout << "An order has been created" << std::endl;
}

Orders::Orders(const Orders& ord)
{
    valid = ord.valid;
}

Orders::~Orders()
{
    std::cout << "Order has been destroyed" << std::endl;
}

void Orders::setValid(bool isValid)
{
    valid = isValid;
}

std::string Orders::describe()
{
    return "Generic Order";
}

void Orders::validate()
{
    setValid(true);
    std::cout << "Default validation statement" << std::endl;
}
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

deployOrder::deployOrder()
{
    std::cout << "Deploy order has been created" << std::endl;
}

deployOrder::deployOrder(const deployOrder& ord)
{
    valid = ord.valid;
}

deployOrder::~deployOrder()
{
    std::cout << "Deploy order has been destroyed" << std::endl;
}

std::string deployOrder::describe()
{
    return "Deploy Order";
}

void deployOrder::validate()
{
    setValid(true);
    std::cout << "Deploy order validation statement" << std::endl;
}

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

advanceOrder::advanceOrder()
{
    std::cout << "Advance order has been created" << std::endl;
}

advanceOrder::advanceOrder(const advanceOrder& ord)
{
    valid = ord.valid;
}

advanceOrder::~advanceOrder()
{
    std::cout << "Advance order has been destroyed" << std::endl;
}

std::string advanceOrder::describe()
{
    return "Advance Order";
}

void advanceOrder::validate()
{
    setValid(true);
    std::cout << "Advance order is validated." << std::endl;
}

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

bombOrder::bombOrder()
{
    std::cout << "Bomb order has been created" << std::endl;
}

bombOrder::bombOrder(const bombOrder& ord)
{
    valid = ord.valid;
}

bombOrder::~bombOrder()
{
    std::cout << "Bomb order has been destroyed" << std::endl;
}

std::string bombOrder::describe()
{
    return "Bomb Order";
}

void bombOrder::validate()
{
    setValid(true);
    std::cout << "Bomb order is validated." << std::endl;
}

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

blockadeOrder::blockadeOrder()
{
    std::cout << "Blockade order has been created" << std::endl;
}

blockadeOrder::blockadeOrder(const blockadeOrder& ord)
{
    valid = ord.valid;
}

blockadeOrder::~blockadeOrder()
{
    std::cout << "Blockade order has been destroyed" << std::endl;
}

std::string blockadeOrder::describe()
{
    return "Blockade Order";
}

void blockadeOrder::validate()
{
    setValid(true);
    std::cout << "Blockade order is validated." << std::endl;
}

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

airliftOrder::airliftOrder()
{
    std::cout << "Airlift order has been created" << std::endl;
}

airliftOrder::airliftOrder(const airliftOrder& ord)
{
    valid = ord.valid;
}

airliftOrder::~airliftOrder()
{
    std::cout << "Airlift order has been destroyed" << std::endl;
}

std::string airliftOrder::describe()
{
    return "Airlift Order";
}

void airliftOrder::validate()
{
    setValid(true);
    std::cout << "Airlift order is validated." << std::endl;
}

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

negotiateOrder::negotiateOrder()
{
    std::cout << "Negotiate order has been created" << std::endl;
}

negotiateOrder::negotiateOrder(const negotiateOrder& ord)
{
    valid = ord.valid;
}

negotiateOrder::~negotiateOrder()
{
    std::cout << "Negotiate order has been destroyed" << std::endl;
}

std::string negotiateOrder::describe()
{
   return "Negotiate Order";
}

void negotiateOrder::validate()
{
    setValid(true);
    std::cout << "Negotiate order is validated." << std::endl;
}

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

OrdersList::OrdersList()
{
    ordersList = new std::vector<Orders*>();
    std::cout << "An order list has been created." << std::endl;
}

OrdersList::OrdersList(const OrdersList& ord)
{
    ordersList = new std::vector<Orders*>();
    for (int i = 0; i < ord.ordersList->size(); i++)
    {
        ordersList->push_back(ord.ordersList->at(i));
    }
}
OrdersList::~OrdersList()
{
    for ( Orders* o : *ordersList)
    {
        delete o;
    }
    delete ordersList;
}

void OrdersList::add(Orders* order)
{
    ordersList->push_back(order);
    std::cout << "An order has been added" << std::endl;
}

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
void OrdersList::move(Orders* order, int position)
{
    std::vector<Orders*>::iterator itr1 = ordersList->begin();
    int index = findOrderIndex(*ordersList, order);
    std::advance(itr1, position);
    ordersList->emplace(itr1, order);
    ordersList->erase(ordersList->begin() + index + 1);
    std::cout << "The order has been moved" << std::endl;
}

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
        out << "Order: "<< *o << std::endl;
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