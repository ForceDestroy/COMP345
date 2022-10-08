// ************* PLEASE READ THIS **********************
// This is not complete as I need to see how other classes work to validate orders (i.e players and cards), this is just placeholders paramaters
// Ideally the orders will receive pointers to players/cards data
#include <iostream>
#include <vector>

class Order { // This generic Order class is never going to be called
    public:
        bool valid = false;
        Order()
        {
            validate();
        }
        Order(const Order& ord)
        {
            valid = ord.valid;
        }
        ~Order()
        {
            std::cout << "Order has been destroyed";
        }
        void setValid(bool isValid)
        {
            valid = isValid;
        }
        virtual void describe()
        {
            std::cout << "This is a generic order.";
        }
        virtual void execute() { // only execute if valid is true
            std::cout << "Blank order execute";
            describe();
        }
        virtual void validate() { // validate orders-specific conditions
            valid = true;
            std::cout << "Default validation statement";
        }
};

// execute method for subclases not required now and will be added later
// deploy checks for valid: selected player, selected territory, target territory (owned by selected player), troop number (available reserves)
class deploy : Order {
    public:
        deploy(bool validSelected, bool validTarget, bool validTroopNumber)
        {
            if (validSelected && validTarget && validTroopNumber)
                validate();
            else
                std::cout << "This deploy order is not valid.";
        }
        deploy(const deploy& ord)
        {
            valid = ord.valid;
        }
        deploy()
        {
            validate();
        }
        ~deploy()
        {
            std::cout << "Deploy order has been destroyed";
        }
        void describe()
        {
            std::cout << "This order adds troops from reserves to selected owned territories.";
        }
        void execute() {
            if (valid){
                std::cout << "Deploy order is executed.";
                describe();
            }
        }
        void validate() {
            valid = true;
            std::cout << "deploy order is validated.";
        }
};
// advance checks for valid: selected player, selected territory, target territory, troop number
class advance : Order {
    public :
        advance(bool validSelected, bool validTarget, bool validTroopNumber)
        // check if player issuing order owns selected and target territory, check if troop number is not over available troops
        {
            if (validSelected && validTarget && validTroopNumber)
                validate();
            else
                std::cout << "This advance order is not valid.";
        }
        advance(const advance& ord)
        {
            valid = ord.valid;
        }
        advance()
        {
            validate();
        }
        ~advance()
        {
            std::cout << "Advance order has been destroyed";
        }
        void describe()
        {
            std::cout << "This order will move troop to selected adjacent territory. If this territory is owned by an enemy, attack that territory";
        }
        void execute() {
            if (valid) {
                std::cout << "Advance order is executed.";
                describe();
            }
        }
        void validate() {
            valid = true;
            std::cout << "advance order is validated.";
        }
};
// bomb checks for valid: selected player, target territory (adjacent to owned territory), card availability
class bomb : Order {
    public :
        bomb(bool hasCard, bool validTarget)
            // check if player has bomb card, check if target territory is next to owned territory
        {
            if (hasCard && validTarget)
                validate();
            else
                std::cout << "This bomb order is not valid.";
        }
        bomb(const bomb& ord)
        {
            valid = ord.valid;
        }
        bomb()
        {
            validate();
        }
        ~bomb()
        {
            std::cout << "Bomb order has been destroyed";
        }
        void describe()
        {
            std::cout << "This order removes half the troops of the selected territory.";
        }
        void execute() {
            if (valid) {
                std::cout << "Bomb order is executed.";
                describe();
            }
        }
        void validate() {
            valid = true;
            std::cout << "bomb order is validated.";
        }
};
// blockade checks for: selected territory, card availability
class blockade : Order {
    public :
        blockade(bool hasCard, bool validSelected)
            // check if player has card and owns selected territory
        {
            if (hasCard && validSelected)
                validate();
            else
                std::cout << "This blockade order is not valid";
        }
        blockade(const blockade& ord)
        {
            valid = ord.valid;
        }
        blockade()
        {
            validate();
        }
        ~blockade()
        {
            std::cout << "Blockade order has been destroyed";
        }
        void describe()
        {
            std::cout << "This order doubles the amount of troops in selected owned territory but turns it neutral at the end of the turn";
        }
        void execute() {
            if (valid) {
                std::cout << "Blockade order is executed.";
                describe();
            }
        }
        void validate() {
            valid = true;
            std::cout << "blockade order is valided.";
        }
};
// airlift order checks for valid: selected player, selected territory, target territory, troop number, card availability
class airlift : Order {
    public :
        airlift(bool selectedPlayerHasCard, bool validSelectedTerritory, bool validTargetTerritory, bool validTroopNumber)
        //check player using has airlift card, check if selected territory and target territory is owned by player, check if number of troops being moved exceeds available troops in selected territory
        {
            if (selectedPlayerHasCard && validSelectedTerritory && validTargetTerritory && validTroopNumber)
                validate();
            else
                std::cout << "This airlift order is not valid.";
        }
        airlift()
        {
            validate();
        }
        airlift(const airlift& ord)
        {
            valid = ord.valid;
        }
        ~airlift()
        {
            std::cout << "Airlift order has been destroyed";
        }
        void describe()
        {
            std::cout << "This order moves troops to owned territories, regardless of distance.";
        }
        void execute() {
            if (valid) {
                std::cout << "Airlift order is executed.";
                describe();
            }
        }
        void validate() {
            valid = true;
            std::cout << "airlift order is validated.";
        }
};
// airlift checks for valid: selected player, target player, card availability
class negotiate : Order {
    public :
        negotiate(bool selectedPlayerHasCard, bool validPlayerName)
        //need to check if player issuing order has the negotiate card, and target player is a real player still in the game
        {
            if (selectedPlayerHasCard && validPlayerName)
                validate();
            else       
                std::cout << "This negotiate order is not valid.";
        }
        negotiate()
        {
            validate();
        }
        negotiate(const negotiate& ord)
        {
            valid = ord.valid;
        }
        ~negotiate()
        {
            std::cout << "Negotiate order has been destroyed";
        }
        void describe()
        {
            std::cout << "This order prevents target from attacking user for 1 turn.";
        }
        void execute() {
            if (valid) {
                std::cout << "advance order is executed.";
                describe();
            }
        }
        void validate() {
            valid = true;
            std::cout << "negotiate order is validated.";
        }
};

class OrdersList
{
    public:
        std::vector<Order*> ordersList;
        void remove(int position) // Orders start from 1 but positions start from 0
        {
            std::vector<Order*>::iterator itr1 = ordersList.begin();
            std::advance(itr1, position);
            ordersList.erase(itr1);
            std::cout << "The order has been deleted";
        }
        void move(Order* odr, int position)
        {
            std::vector<Order*>::iterator itr1 = ordersList.begin();
            std::advance(itr1, position);
            ordersList.emplace(itr1, odr);
            std::cout << "The order has been moved";
        }
        void add(Order* odr)
        {
            ordersList.push_back(odr);
            std::cout << "An order has been added";
        }
};
