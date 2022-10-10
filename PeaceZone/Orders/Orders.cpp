#include "Orders.h"

Orders::Orders()
{
    valid = false;
    std::cout << "An order has been created";
}

Orders::Orders(const Orders& ord)
{
    valid = ord.valid;
}

Orders::~Orders()
{
    std::cout << "Order has been destroyed";
}

void Orders::setValid(bool isValid)
{
    valid = isValid;
}

void Orders::describe()
{
    std::cout << "This is a generic order.";
}

void Orders::validate()
{
    setValid(true);
    std::cout << "Default validation statement";
}
void Orders::execute()
{
    validate();
            if (valid)
            {
                std::cout << "Blank order execute";
                describe();
            }
            else
            {
                std::cout << "This order is not valid.";
            }
}

Orders& Orders::operator=(const Orders &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const Orders &orders)
{
    out << "This is a generic order.";
    return out;
}

deployOrder::deployOrder()
{
    std::cout << "Deploy order has been created";
}

deployOrder::deployOrder(bool validSelected, bool validTarget, bool validTroopNumber)
{
    std::cout << "Deploy order has been created.";
}

deployOrder::deployOrder(const deployOrder& ord)
{
    valid = ord.valid;
}

deployOrder::~deployOrder()
{
    std::cout << "Deploy order has been destroyed";
}

void deployOrder::describe()
{
    std::cout << "This order adds troops from reserves to selected owned territories.";
}

void deployOrder::validate()
{
    setValid(true);
    std::cout << "Deploy order validation statement";
}

void deployOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Deploy order execute";
        describe();
    }
    else
    {
        std::cout << "This order is not valid.";
    }
}

deployOrder& deployOrder::operator=(const deployOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const deployOrder &orders)
{
    out << "This order adds troops from reserves to selected owned territories.";
    return out;
}

advanceOrder::advanceOrder()
{
    std::cout << "Advance order has been created";
}

advanceOrder::advanceOrder(bool validSelected, bool validTarget, bool validTroopNumber)
{
    std::cout << "Advance order has been created.";
}

advanceOrder::advanceOrder(const advanceOrder& ord)
{
    valid = ord.valid;
}

advanceOrder::~advanceOrder()
{
    std::cout << "Advance order has been destroyed";
}

void advanceOrder::describe()
{
    std::cout << "This order will move troop to selected adjacent territory. If this territory is owned by an enemy, attack that territory";
}

void advanceOrder::validate()
{
    setValid(true);
    std::cout << "Advance order is validated.";
}

void advanceOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Advance order is executed";
        describe();
    }
    else
    {
        std::cout << "This order is not valid.";
    }
}

advanceOrder& advanceOrder::operator=(const advanceOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const advanceOrder &orders)
{
    out << "This order will move troop to selected adjacent territory. If this territory is owned by an enemy, attack that territory";
    return out;
}

bombOrder::bombOrder()
{
    std::cout << "Bomb order has been created";
}

bombOrder::bombOrder(bool hasCard, bool validTarget)
{
    std::cout << "Bomb order has been created.";
}

bombOrder::bombOrder(const bombOrder& ord)
{
    valid = ord.valid;
}

bombOrder::~bombOrder()
{
    std::cout << "Bomb order has been destroyed";
}

void bombOrder::describe()
{
    std::cout << "This order removes half the troops of the selected territory.";
}

void bombOrder::validate()
{
    setValid(true);
    std::cout << "Bomb order is validated.";
}

void bombOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Bomb order is executed";
        describe();
    }
    else
    {
        std::cout << "This bomb order is not valid.";
    }
}

bombOrder& bombOrder::operator=(const bombOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const bombOrder &orders)
{
    out << "This order removes half the troops of the selected territory.";
    return out;
}

blockadeOrder::blockadeOrder()
{
    std::cout << "Blockade order has been created";
}

blockadeOrder::blockadeOrder(bool hasCard, bool validSelected)
{
    std::cout << "Blockade order has been created.";
}

blockadeOrder::blockadeOrder(const blockadeOrder& ord)
{
    valid = ord.valid;
}

blockadeOrder::~blockadeOrder()
{
    std::cout << "Blockade order has been destroyed";
}

void blockadeOrder::describe()
{
    std::cout << "This order doubles the amount of troops in selected owned territory but turns it neutral at the end of the turn";
}

void blockadeOrder::validate()
{
    setValid(true);
    std::cout << "Blockade order is validated.";
}

void blockadeOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Blockade order is executed";
        describe();
    }
    else
    {
        std::cout << "This blockade order is not valid.";
    }
}

blockadeOrder& blockadeOrder::operator=(const blockadeOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const blockadeOrder &orders)
{
    out << "This order doubles the amount of troops in selected owned territory but turns it neutral at the end of the turn";
    return out;
}

airliftOrder::airliftOrder()
{
    std::cout << "Airlift order has been created";
}

airliftOrder::airliftOrder(bool selectedPlayerHasCard, bool validSelectedTerritory, bool validTargetTerritory, bool validTroopNumber)
{
    std::cout << "Airlift order has been created.";
}

airliftOrder::airliftOrder(const airliftOrder& ord)
{
    valid = ord.valid;
}

airliftOrder::~airliftOrder()
{
    std::cout << "Airlift order has been destroyed";
}

void airliftOrder::describe()
{
    std::cout << "This order moves troops to owned territories, regardless of distance.";
}

void airliftOrder::validate()
{
    setValid(true);
    std::cout << "Airlift order is validated.";
}

void airliftOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Airlift order is executed";
        describe();
    }
    else
    {
        std::cout << "This airlift order is not valid.";
    }
}

airliftOrder& airliftOrder::operator=(const airliftOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const airliftOrder &orders)
{
    out << "This order moves troops to owned territories, regardless of distance.";
    return out;
}

negotiateOrder::negotiateOrder()
{
    std::cout << "Negotiate order has been created";
}

negotiateOrder::negotiateOrder(bool selectedPlayerHasCard, bool validPlayerName)
{
    std::cout << "Negotiate order has been created.";
}

negotiateOrder::negotiateOrder(const negotiateOrder& ord)
{
    valid = ord.valid;
}

negotiateOrder::~negotiateOrder()
{
    std::cout << "Negotiate order has been destroyed";
}

void negotiateOrder::describe()
{
    std::cout << "This order prevents target from attacking user for 1 turn.";
}

void negotiateOrder::validate()
{
    setValid(true);
    std::cout << "Negotiate order is validated.";
}

void negotiateOrder::execute()
{
    validate();
    if (valid)
    {
        std::cout << "Negotiate order is executed";
        describe();
    }
    else
    {
        std::cout << "This negotiate order is not valid.";
    }
}

negotiateOrder& negotiateOrder::operator=(const negotiateOrder &ord)
{
    valid = ord.valid;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const negotiateOrder &orders)
{
    out << "This order prevents target from attacking user for 1 turn.";
    return out;
}

OrdersList::OrdersList()
{
    std::cout << "An order list has been created.";
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
    std::cout << "An order has been added";
}

void OrdersList::remove(int position)
{
    Orders* order = (*ordersList)[position];
    ordersList->erase(ordersList->begin() + position);
    delete order;
    std::cout << "An order has been removed";
}

void OrdersList::move(Orders* order, int position)
{
    std::vector<Orders*>::iterator itr1 = ordersList->begin();
    std::advance(itr1, position);
    ordersList->emplace(itr1, order);
    std::cout << "The order has been moved";
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
    for (int i = 0; i < orders.ordersList->size(); i++)
    {
        out << "Order: "<<orders.ordersList->at(i) << std::endl;
    }
    return out;
}
