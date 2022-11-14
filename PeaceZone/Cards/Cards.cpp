#include "Cards.h"
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "../Orders/Orders.h"
#pragma region Card

//Destructor - Card
Card::~Card(){

}

//Constructor - Card
Card::Card(CardType type, Deck* deck) {
	this->type = type;
	this->deck = deck;
}

//Copy Constructor - Card
Card::Card(const Card& c) {
	type = c.type;
	deck = c.deck;
}

//Operator assignement - Card
Card& Card::operator=(const Card& c) {

	if (this != &c) {
		type = c.type;
		deck = c.deck;
	}

	return *this;
}

//Play function removes card from hand, returns it to deck and creates a new order to be added to player's list
void Card::Play(Hand& h, OrdersList& o) {
	h.Remove(this);
	deck->Insert(this);

	switch (type)
	{
	case bomb:
	{
		o.add(new bombOrder());
		break;
	}
	case blockade:
	{
		o.add(new blockadeOrder());
		break;
	}
	case airlift:
	{
		o.add(new airliftOrder());
		break;
	}
	case diplomacy:
	{
		o.add(new negotiateOrder());
		break;
	}
	case reinforcement:
	{
		//Add more reinforcements to the player
			break;
	}
	default:
		break;
	}
	
}

//OSstream operator - Card
std::ostream& operator<<(std::ostream& os, const Card& c) {

	os << "Card: ";

	switch (c.type)
	{
	case bomb:
	{
			os << "Bomb" << std::endl;
			break;
	}
	case blockade:
	{
		os << "Blockade" << std::endl;
		break;
	}
	case airlift:
	{
		os << "Airlift" << std::endl;
		break;
	}
	case diplomacy:
	{
		os << "Diplomacy" << std::endl;
		break;
	}
	case reinforcement:
	{
		os << "Reinforcement" << std::endl;
		break;
	}
	default:
		break;
	}

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

	for (int i = 0; i < NUMBER_BOMB_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		listOfCards->push_back(new Card(bomb, this));
	}

	for (int i = 0; i < NUMBER_BLOCKADE_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		listOfCards->push_back(new Card(blockade, this));
	}

	for (int i = 0; i < NUMBER_AIRLIFT_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		listOfCards->push_back(new Card(airlift, this));
	}

	for (int i = 0; i < NUMBER_DIPLOMACY_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		listOfCards->push_back(new Card(diplomacy, this));
	}

	for (int i = 0; i < NUMBER_REINFORCEMENT_CARDS; i++) {

		//Cards are deleted when Deck or Hand containing them is deleted
		listOfCards->push_back(new Card(reinforcement, this));
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
	os << "\nDeck contains the following cards:"<< std::endl;
	for(Card* c : *d.listOfCards)
	{
		os << *c;
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
		std::cout << "\nInvalid function call, you are trying to remove a card from a Hand in which it was not contained." << std::endl;
	}
}

//OsStream Operator - Hand
std::ostream& operator<<(std::ostream& os, const Hand& h) {
	os << "\nHand contains the following cards:" << std::endl;

	for (Card* c : *h.listOfCards)
	{
		os << *c;
	}
	return os;
}
Card* Hand::operator [](int ItemKey) {
	return (*listOfCards)[ItemKey];
}
#pragma endregion