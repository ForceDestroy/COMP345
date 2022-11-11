#pragma once
#include <iostream>
#include <vector>
#include "../Orders/Orders.h"

class Deck;
class Hand;
enum CardType
{
	bomb = 0,
	blockade = 1,
	airlift = 2,
	diplomacy = 3,
	reinforcement = 4
};
class Card {
private:
	CardType type;
	//Cards should remember what deck they are from since Play function needs to return card to deck
	Deck* deck;
public:
	//Do not want a default constructor because order types should be specified
	Card(CardType type, Deck* deck);
	Card(const Card& c);
	~Card();
	Card& operator=(const Card& p);
	void Play( Hand& h, OrdersList& o);
	friend std::ostream& operator<<(std::ostream& os, const Card& c);
};

class Deck {
private:
	std::vector<Card*>* listOfCards;
	void PopulateDeck();
	const int NUMBER_BOMB_CARDS = 3;
	const int NUMBER_BLOCKADE_CARDS = 3;
	const int NUMBER_AIRLIFT_CARDS = 3;
	const int NUMBER_DIPLOMACY_CARDS = 3;
	const int NUMBER_REINFORCEMENT_CARDS = 3;
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
public:
	std::vector<Card*>* listOfCards;
	Hand();
	Hand(const Hand& hand);
	~Hand();
	Hand& operator=(const Hand& h);
	void Insert(Card* c);
	void Remove(Card* c);
	friend std::ostream& operator<<(std::ostream& os, const Hand& h);
	Card* operator [](int ItemKey);

};