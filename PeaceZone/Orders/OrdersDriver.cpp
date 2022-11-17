#include "Orders.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"

inline void testOrdersList()
{
	OrdersList* orderList = new OrdersList();

	deployOrder* deploy = new deployOrder();
	deploy->validate();
	deploy->execute();
	orderList->add(deploy);

	advanceOrder* advance = new advanceOrder();
	advance->validate();
	advance->execute();
	orderList->add(advance);
	
	bombOrder* bomb = new bombOrder();
	bomb->validate();
	bomb->execute();
	orderList->add(bomb);

	blockadeOrder* blockade = new blockadeOrder();
	blockade->validate();
	blockade->execute();
	orderList->add(blockade);

	airliftOrder* airlift = new airliftOrder();
	airlift->validate();
	airlift->execute();
	orderList->add(airlift);

	negotiateOrder* negotiate = new negotiateOrder();
	negotiate->validate();
	negotiate->execute();
	orderList->add(negotiate);

	std::cout << *orderList << std::endl;

	orderList->move(negotiate, 0);

	std::cout << *orderList << std::endl;

	orderList->remove(negotiate);

	std::cout << *orderList << std::endl;

	delete orderList;

}

inline void testOrderExecution()
{
	Territory* t1 = new Territory(1, "t1", 1);
	Territory* t2 = new Territory(2, "t2", 2);
	Territory* t3 = new Territory(3, "t3", 3);
	Territory* t4 = new Territory(4, "t4", 4);

	Player* p1 = new Player("p1");
	Player* p2 = new Player("p2");
	Player* p3 = new Player("p3");
	Player* p4 = new Player("NEUTRAL");

	Deck* gameDeck = new Deck();

	p1->reinforcementPool = 10;

	t1->neighbors.push_back(t2);
	t1->owner = p1;
	t1->armyCount = 900;

	t2->neighbors.push_back(t1);
	t2->neighbors.push_back(t4);
	t2->owner = p2;
	t2->armyCount = 2;

	//t3 not a neighbor of anyone
	t3->owner = p3;
	t3->armyCount = 20;

	t4->neighbors.push_back(t2);
	t4->owner = p2;
	t4->armyCount = 5;

	//do1, do2, do3 is invalid, do4 is valid
	//demonstrates, player ownership of territory, checking troops number
	deployOrder* do1 = new deployOrder(p1, t1, 20); // over troops limit
	deployOrder* do2 = new deployOrder(p1, t3, 10); //does not own territory
	deployOrder* do3 = new deployOrder(p2, t1, 20); // does not own territory
	deployOrder* do4 = new deployOrder(p1, t1, 10); // valid order
	do1->execute();
	do2->execute();
	do3->execute();
	do4->execute();

	// Checks for ownership of territory after attack
	std::cout << "Original owner of territory is: " << *t2->owner << std::endl;
	std::cout << "P1's current hand of card: " << std::endl;
	std::cout << *p1->handOfCards << std::endl;
	advanceOrder* ao1 = new advanceOrder(p1, t1, t2, 500); // must succeed
	ao1->execute();
	std::cout << "Owner of territory 2 is now: " << *t2->owner << std::endl;
	std::cout << "P1's current hand of card: " << std::endl;
	std::cout << *p1->handOfCards << std::endl;


	//Bomb order
	bombOrder* bomInvalid = new bombOrder(p1, t3); //Invalid due to not being a neigbor
	bomInvalid->execute();
	std::cout << "T4's original troop count: " << t4->armyCount << std::endl;
	bombOrder* bomO1 = new bombOrder(p1, t4);
	bomO1->execute();
	std::cout << "T4's current army count: " << t4->armyCount << std::endl;

	//Airlift order
	std::cout << "T1's current army count: " << t1->armyCount << std::endl;
	std::cout << "T2's current army count: " << t2->armyCount << std::endl;
	airliftOrder* airO1 = new airliftOrder(p1, t1, t2, 30);
	airO1->execute();
	std::cout << "T1's current army count: " << t1->armyCount << std::endl;
	std::cout << "T2's current army count: " << t2->armyCount << std::endl;


	// Checks for attacks blocked by negotiate
	negotiateOrder* no1 = new negotiateOrder(p1, p2);
	no1->execute();
	advanceOrder* ao2 = new advanceOrder(p1, t2, t4, 100); // blocked by negotiate
	ao2->execute();

	// Checks for ownership change after blockade order
	std::cout << "T1's current owner: " << *t1->owner << std::endl;
	blockadeOrder* bo1 = new blockadeOrder(p1, t1);
	bo1->execute();
	std::cout << "T1's new owner: " << *t1->owner << std::endl;
}