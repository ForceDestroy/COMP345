#pragma once
#include <iostream>
#include <vector>
class Orders;
class Deck;
class Hand;

class Card {
private:
	Orders* order;
	//Cards should remember what deck they are from since Play function needs to return card to deck
	Deck* deck;
public:
	//Do not want a default constructor because order types should be specified
	Card(Orders* order, Deck* deck);
	Card(const Card& c);
	~Card();
	Card& operator=(const Card& p);
	Orders* Play( Hand& h);
	friend std::ostream& operator<<(std::ostream& os, const Card& c);
};

class Deck {
private:
	std::vector<Card*>* listOfCards;
	void PopulateDeck();
	const int NUMBER_DEPLOY_CARDS = 2;
	const int NUMBER_ADVANCE_CARDS = 2;
	const int NUMBER_BOMB_CARDS = 2;
	const int NUMBER_BLOCKADE_CARDS = 2;
	const int NUMBER_AIRLIFT_CARDS = 2;
	const int NUMBER_NEGOTIATE_CARDS = 2;
public:
	Deck();
	Deck(const Deck& deck);
	~Deck();
	Deck& operator=(const Deck& d);
	void Shuffle();
	Card* Draw();
	void Insert(Card* c);
	friend std::ostream& operator<<(std::ostream& os, const Deck& d);

};

class Hand {
private:
	std::vector<Card*>* listOfCards;
public:
	Hand();
	Hand(const Hand& hand);
	~Hand();
	Hand& operator=(const Hand& h);
	void Insert(Card* c);
	void Remove(Card* c);
	friend std::ostream& operator<<(std::ostream& os, const Hand& h);
	Card* operator [](int ItemKey);

};