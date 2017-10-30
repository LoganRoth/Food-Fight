#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <..\scugog_project\src\player.h>


using namespace std;

int main() {
	Player player1(0, 1);
	Player player2(1, 2);

	player1.draw_card();
	player1.draw_card();
	for (auto &card : player1.get_hand()) {
		cout << card;
	}


	cout << player1.get_deck().get_size() << endl;
	cout << player2.get_deck().get_size() << endl;

	std::string line;
	std::getline(std::cin, line);
}
