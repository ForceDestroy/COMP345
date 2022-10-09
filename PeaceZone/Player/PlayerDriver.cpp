#include "Player.h"

void testPlayer(){
    std::cout << "Testing Player class" << std::endl;
    std::vector<Territory*>* territories = new std::vector<Territory*>();
    //creating territories
    Territory t1 = Territory("t1");
    Territory t2 = Territory("t2");
    Territory t3 = Territory("t3");
    //adding territories to vector
    territories->push_back(&t1);
    territories->push_back(&t2);
    territories->push_back(&t3);

    Hand* handOfCards = new Hand();
    OrdersList* listOfOrders = new OrdersList();
    Order o1 = Order();

    Player* player = new Player(territories, handOfCards, listOfOrders);
    std::cout << *player << std::endl;
    //testing the methods in player
    std::cout << "toAttack method" << std::endl;
    player->toAttack();
    std::cout << "toDefend method" << std::endl;
    player->toDefend();
    std::cout << "issueOrder method" << std::endl;
    player->issueOrder(o1);
    std::cout << *player << std::endl;
    std::cout << "delete player" << std::endl;
    delete player;
    std::cout << "testPlayer done" << std::endl;
}