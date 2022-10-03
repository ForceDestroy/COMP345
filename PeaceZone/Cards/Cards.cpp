#include "Cards.h"
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#pragma region Card

//Destructor - Card
Card::~Card(){
	delete order;
}

//Constructor - Card
Card::Card(Orders* order, Deck* deck) {
	this->order = order;
	this->deck = deck;
}

//Copy Constructor - Card
Card::Card(const Card& c) {
	order = c.order;
	deck = c.deck;
}

//Operator assignement - Card
Card& Card::operator=(const Card& c) {

	if (this != &c) {
		order = c.order;
		deck = c.deck;
	}

	return *this;
}

//Play function removes card from hand, returns it to deck and creates a new order to be added to player's list
Orders* Card::Play(Hand& h) {
	h.Remove(this);
	deck->Insert(this);

	//Order will be deleted when it is executed
	// TODO Order implementation
	//return new Orders(order);
	
}

//OSstream operator - Card
std::ostream& operator<<(std::ostream& os, const Card& c) {

	os << "Card: " << std::endl;

	//Waiting for Order
	//out << *order << std::endl;

	return os;
}

#pragma endregion

#pragma region Deck


//Default constructor - Deck
Deck::Deck() {
	listOfCards = new std::vector<Card*>();

	PopulateDeck();

	Shuffle();
}

void Deck::PopulateDeck() {
	//Create all the cards for the deck

	//Orders are deleted when Card containing them is deleted	
	//TODO use specific order constructor
	//Orders* deployOrder = new Orders;

	for (int i = 0; i < NUMBER_DEPLOY_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		//listOfCards->push_back(new Card(deployOrder));
	}

	//TODO use specific order constructor
	//Orders* advanceOrder = new Orders;

	for (int i = 0; i < NUMBER_ADVANCE_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		//listOfCards->push_back(new Card(advanceOrder));
	}

	//TODO use specific order constructor
	//Orders* bombOrder = new Orders;

	for (int i = 0; i < NUMBER_BOMB_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		//listOfCards->push_back(new Card(bombOrder));
	}

	//TODO use specific order constructor
	//Orders* blockadeOrder = new Orders;

	for (int i = 0; i < NUMBER_BLOCKADE_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		//listOfCards->push_back(new Card(blockadeOrder));
	}

	//TODO use specific order constructor
	//Orders* airliftOrder = new Orders;

	for (int i = 0; i < NUMBER_AIRLIFT_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		//listOfCards->push_back(new Card(airliftOrder));
	}

	//TODO use specific order constructor
	//Orders* negotiateOrder = new Orders;

	for (int i = 0; i < NUMBER_NEGOTIATE_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		//listOfCards->push_back(new Card(negotiateOrder));
	}
}

//Copy Constructor - Deck
Deck::Deck(const Deck& deck) {
	listOfCards = new std::vector<Card*>();

	for(Card * c : *deck.listOfCards)
	{
		listOfCards->push_back(new Card(*c));
	}
}

//Default destructor - Deck
Deck::~Deck() {
	for (Card* c : *listOfCards)
	{
		delete c;
	}
	delete listOfCards;
}

//Operator assignement - Deck
Deck& Deck::operator=(const Deck& d) {
	if (this != &d) {
		listOfCards = d.listOfCards;
	}
	return *this;
}

//Shuffle the contents of the deck
void Deck::Shuffle() {
	// create a seed from current time to shuffle deck
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::shuffle(listOfCards->begin(), listOfCards->end(), std::default_random_engine(seed));
}

//Return the top card of the deck
Card* Deck::Draw() {
	Card* drawn = listOfCards->back();
	listOfCards->pop_back();
	return drawn;
}
//Add a card back to the deck and shuffle
void Deck::Insert(Card* c) {
	listOfCards->push_back(c);
	Shuffle();
}

//OsStream operator - Deck
std::ostream& operator<<(std::ostream& os, const Deck& d) {
	os << "Deck contains the following cards:\n"<< std::endl;
	for(Card* c : *d.listOfCards)
	{
		os << c << "\n" << std::endl;
	}
	return os;
}

#pragma endregion

#pragma region Hand
//Default Constructor - Hand
Hand::Hand() {
	listOfCards = new std::vector<Card*>();
}

//Copy constructor - Hand
Hand::Hand(const Hand& hand) {
	listOfCards = new std::vector<Card*>();

	for(Card* c : *hand.listOfCards)
	{
		listOfCards->push_back(new Card(*c));
	}
}

//Default destructor - Hand
Hand::~Hand() {
	for(Card * c : *listOfCards)
	{
		delete c;
	}
	delete listOfCards;
}

//Asignment operator - Hand
Hand& Hand::operator=(const Hand& h) {
	if (this != &h) {
		listOfCards = h.listOfCards;
	}
	return *this;
}

//Add a card to the hand
void Hand::Insert(Card* c) {
	listOfCards->push_back(c);
}

//Remove a card from the hand
void Hand::Remove(Card* c) {
	auto cardToRemove = std::find(listOfCards->begin(), listOfCards->end(), c);
	if (cardToRemove != listOfCards->end())
		listOfCards->erase(cardToRemove);
	else {
		std::cout << "Invalid function call, you are trying to remove a card from a Hand in which it was not contained.";
	}
}

//OsStream Operator - Hand
std::ostream& operator<<(std::ostream& os, const Hand& h) {
	os << "Hand contains the following cards:\n" << std::endl;

	for (Card* c : *h.listOfCards)
	{
		os << c << "\n" << std::endl;
	}
	return os;
}
Card* Hand::operator [](int ItemKey) {
	return (*listOfCards)[ItemKey];
}
#pragma endregion