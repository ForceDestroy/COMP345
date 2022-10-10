#include "Player.h"

void testPlayer(){
    std::cout << "Testing Player class" << std::endl;
    std::vector<Territory*>* territories = new std::vector<Territory*>();
    //creating territories for the player for testing
    Territory* t1 = new Territory(0,"t1",1);
    Territory* t2 = new Territory(1,"t2",1);
    Territory* t3 = new Territory(2,"t3",1);
    //creating territories for the player to attack
    Territory* t4 = new Territory(3,"t4",1);
    Territory* t5 = new Territory(4,"t5",1);
    //adding territories to vector
    territories->push_back(t1);
    territories->push_back(t2);
    territories->push_back(t3);
    //creating neighbors for the player to attack
    t3->neighbors.push_back(t4);
    t4->neighbors.push_back(t3);
    t3->neighbors.push_back(t5);
    t5->neighbors.push_back(t3);

    //creating hand and orders list
    Hand* handOfCards = new Hand();
    OrdersList* listOfOrders = new OrdersList();

    //creating player
    Player* player = new Player(territories, handOfCards, listOfOrders);
    std::cout << *player << std::endl;
    //testing the methods in player
    std::cout << "toAttack method" << std::endl;
    player->toAttack();
    std::cout << "toDefend method" << std::endl;
    player->toDefend();
    std::cout << "issueOrder method" << std::endl;
    player->issueOrder("deploy");
    std::cout << *player << std::endl;
    std::cout << "delete player" << std::endl;
    //deleting all the territories
    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
    delete player;
    std::cout << "testPlayer done" << std::endl;
}