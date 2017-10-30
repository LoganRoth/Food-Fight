#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <..\scugog_project\src\player.h>

using namespace std;

class Environment {
public:
	// Constructor
	Environment(int number_of_players, vector<int> decks_chosen);

	// Accessor
	bool get_game_on();

	// Other Functions
	void turn();
	void end_game();	// Ends game by setting game_on as false

private:
	int number_of_players;
	int current_player;
	vector<vector<Card>> field;
	vector<Player> players;

	bool game_on;
};

// Basic Exception Class
class EnvironmentException : public exception {
public:
	EnvironmentException(const string& message);
	string& what();

private:
	string message;
};