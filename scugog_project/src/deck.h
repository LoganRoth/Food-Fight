#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <..\scugog_project\src\card.h>

using namespace std;

class Deck {
public:
	Deck();
	Deck(int deck_num);

	int get_deck_num();
	int get_size();
	Card access_card(int index);
	void add_card_to_deck(Card);
	Card pop_card(int index);
	void retrieve_cards();

private:
	int deck_num;
	vector<Card> cards;
};

class DeckException : public exception {
public:
	DeckException(const string& message);
	string& what();

private:
	string message;
};