#pragma once
#include "..\scugog_project\src\player.h"
#include "..\scugog_project\src\card.h"
#include "..\scugog_project\src\deck.h"
#include "..\scugog_project\src\environment.h"
#include "..\scugog_project\src\graveyard.h"
// ALL OF THIS IS TODO STILL WORKING ON IT
class PlayGame
{
public:
	Environment env; // may need to make this private and add getters
	int cardType;
	int secondClickType;
	

	PlayGame(Environment env);
	PlayGame();
	void Play(sf::RenderWindow& window);
	bool inCard(sf::Sprite crd, float mpx, float mpy);
	bool inText(sf::Text text, float mpx, float mpy);
	void handleClicks(vector<sf::Sprite> clicks, vector<Card> cardClicks);
	//Environment getEnvironment();
//private:
	//Environment env;
};