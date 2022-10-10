#include <iostream>
#include <vector>

class Orders
{
    public:
        bool valid = false;
        // Constructors
        Orders();
        Orders(const Orders& ord);
        virtual ~Orders();

        // Methods
        virtual void execute();
        virtual void validate();
        virtual void describe();
        void setValid(bool isValid);
        Orders& operator=(const Orders &);
        friend std::ostream& operator<<(std::ostream &out, const Orders &orders);
};

// execute method for subclases not required now and will be added later
// deploy checks for valid: selected player, selected territory, target territory (owned by selected player), troop number (available reserves)
class deployOrder : public Orders
{
    public:
        // Constructors
        deployOrder();
        deployOrder(const deployOrder& ord);
        ~deployOrder();

        // Methods
        void execute();
        void validate();
        void describe();
        deployOrder& operator=(const deployOrder &);
        friend std::ostream& operator<<(std::ostream &out, const deployOrder &orders);
};

// advance checks for valid: selected player, selected territory, target territory, troop number
class advanceOrder : public Orders
{
    public:
        // Constructors
        advanceOrder();
        advanceOrder(const advanceOrder& ord);
        ~advanceOrder();

        // Methods
        void execute();
        void validate();
        void describe();
        advanceOrder& operator=(const advanceOrder &);
        friend std::ostream& operator<<(std::ostream &out, const advanceOrder &orders);
};
// bomb checks for valid: selected player, target territory (adjacent to owned territory), card availability
class bombOrder : public Orders
{
    public:
        // Constructors
        bombOrder();
        bombOrder(const bombOrder& ord);
        ~bombOrder();

        // Methods
        void execute();
        void validate();
        void describe();
        bombOrder& operator=(const bombOrder &);
        friend std::ostream& operator<<(std::ostream &out, const bombOrder &orders);
};

// blockade checks for: selected territory, card availability
class blockadeOrder : public Orders
{
    public:
        // Constructors
        blockadeOrder();
        blockadeOrder(const blockadeOrder& ord);
        ~blockadeOrder();

        // Methods
        void execute();
        void validate();
        void describe();
        blockadeOrder& operator=(const blockadeOrder &);
        friend std::ostream& operator<<(std::ostream &out, const blockadeOrder &orders);
};

// airlift order checks for valid: selected player, selected territory, target territory, troop number, card availability
class airliftOrder : public Orders
{
    public:
        // Constructors
        airliftOrder();
        airliftOrder(const airliftOrder& ord);
        ~airliftOrder();

        // Methods
        void execute();
        void validate();
        void describe();
        airliftOrder& operator=(const airliftOrder &);
        friend std::ostream& operator<<(std::ostream &out, const airliftOrder &orders);
};

// negotiate order checks for valid: selected player, target player
class negotiateOrder : public Orders
{
    public:
        // Constructors
        negotiateOrder();
        negotiateOrder(const negotiateOrder& ord);
        ~negotiateOrder();

        // Methods
        void execute();
        void validate();
        void describe();
        negotiateOrder& operator=(const negotiateOrder &);
        friend std::ostream& operator<<(std::ostream &out, const negotiateOrder &orders);
};

// OrdersList class
class OrdersList
{
    private:
        std::vector<Orders*>* ordersList;
    public:
        // Constructors
        OrdersList();
        OrdersList(const OrdersList& ord);
        ~OrdersList();

        // Methods
        void add(Orders* order);
        void remove(Orders* order);
        void move(Orders* order, int position);

        //Operators
        OrdersList& operator=(const OrdersList &ord);
        friend std::ostream& operator<<(std::ostream &out, const OrdersList &orders);
        Orders* operator[](int itemKey);
};
