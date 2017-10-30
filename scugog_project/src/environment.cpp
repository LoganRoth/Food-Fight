#pragma once
#include <stdlib.h>
#include <iostream>
#include <random>
#include <random>

#include <..\scugog_project\src\environment.h>

using namespace std;

// Exception
EnvironmentException::EnvironmentException(const string& message) : message(message) {}
string& EnvironmentException::what() { return message; }

// Constructor
Environment::Environment(int num_of_players, vector<int> decks_chosen) {
	game_on = true;
	number_of_players = num_of_players;

	for (int num = 0; num < number_of_players; num++) {
		Player player(decks_chosen[num], num);
		players.push_back(player);
	}

	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(0, number_of_players-1);
	current_player = distr(eng);
}

// Accessors
bool Environment::get_game_on() {
	return game_on;
}

// Other Functions
void Environment::turn() {
	/*Player player = players[current_player];
	bool player_turn = true;
	player.draw_card();
	while (player_turn) {
		player_turn = false;
	}*/

}
void Environment::end_game() {
	game_on = false;
}