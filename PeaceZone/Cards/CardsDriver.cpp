#include "Cards.h"
#include <iostream>
#include "../Orders/Orders.h"

inline void testCards() {

	Deck* d = new Deck();
	Hand* h = new Hand();
	OrdersList* o = new OrdersList();

	//Display the contents of the newly created deck
	std::cout << *d << std::endl;

	//Draw 3 cards from the deck
	h->Insert(d->Draw());
	h->Insert(d->Draw());
	h->Insert(d->Draw());

	//Display the contents of the deck and the hand after drawing
	std::cout << *d << std::endl;
	std::cout << *h << std::endl;

	//Play the cards in hand
	//(*h)[0]->Play(*h, *o);
	//(*h)[0]->Play(*h, *o);
	//(*h)[0]->Play(*h, *o);

	//Display the contents of the deck
	std::cout << *d << std::endl;
	std::cout << *h << std::endl;
	std::cout << *o << std::endl;

	delete d;
	delete h;
	delete o;

}