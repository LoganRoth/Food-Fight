#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <..\scugog_project\src\deck.h>

using namespace std;

class Player {
public:
	Player(int deck_number, int player_number);

	Deck get_deck();
	int get_hp();
	vector<Card> get_hand();

	void set_hp(int hitpoints);
	void set_current_resources(int resources);

	void draw_card();
	void add_card_to_hand(Card card);

private:
	int hitpoints;
	vector<Card> hand;
	Deck current_deck;
	int current_resources;
	int max_resources;
	int player_number;
};

class PlayerException : public exception {
public:
	PlayerException(const string& message);
	string& what();

private:
	string message;
};