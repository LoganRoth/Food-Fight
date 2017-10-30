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
	Environment(int number_of_players, vector<int> decks_chosen);

	void end_game();

private:
	int number_of_players;
	int current_player;
	vector<vector<Card>> field;
	vector<Player> players;

	bool game_on;

};

class EnvironmentException : public exception {
public:
	EnvironmentException(const string& message);
	string& what();

private:
	string message;
};