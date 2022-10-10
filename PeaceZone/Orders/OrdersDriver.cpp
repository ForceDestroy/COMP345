#include "Orders.h"

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