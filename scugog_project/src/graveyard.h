#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <..\scugog_project\src\card.h>

using namespace std;

class Graveyard {
public:
	Graveyard();

	void add_card_to_graveyard(Card);

private:
	vector<Card> graveyard;
};

class GraveyardException : public exception {
public:
	GraveyardException(const string& message);
	string& what();

private:
	string message;
};