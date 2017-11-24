#include "stdafx.h"
#include "PlayGame.h"

void PlayGame::Play(Player p1, Player p2, sf::RenderWindow & renderWindow) 
{
	sf::Texture texture, card;
	sf::Font font;
	// load images needed
	if (!font.loadFromFile("../scugog_project_frontend/resources/fonts/sansation.ttf")) {
		return;
	}

	if (texture.loadFromFile("../scugog_project_frontend/resources/images/bg.jpg") != true)
	{
		return;
	}

	if (card.loadFromFile("../scugog_project_frontend/resources/images/cardc.png") != true)
	{
		return;
	}
	// hand 1
	sf::Sprite p1h1(card);
	sf::Sprite p1h2(card);
	sf::Sprite p1h3(card);
	sf::Sprite p1h4(card);
	sf::Sprite p1h5(card);
	// hand 2
	sf::Sprite p2h1(card);
	sf::Sprite p2h2(card);
	sf::Sprite p2h3(card);
	sf::Sprite p2h4(card);
	sf::Sprite p2h5(card);
	// field 1
	sf::Sprite p1f1(card);
	sf::Sprite p1f2(card);
	sf::Sprite p1f3(card);
	sf::Sprite p1f4(card);
	sf::Sprite p1f5(card);
	// field 2
	sf::Sprite p2f1(card);
	sf::Sprite p2f2(card);
	sf::Sprite p2f3(card);
	sf::Sprite p2f4(card);
	sf::Sprite p2f5(card);
	// deck 1
	sf::Sprite p1d(card);
	// deck 2
	sf::Sprite p2d(card);
	// grave 1
	sf::Sprite p1g(card);
	// grave 2
	sf::Sprite p2g(card);


	sf::Sprite sprite(texture);

	sf::Event event;
	bool gameover = false;
	bool p1Turn = true;
	bool p2Turn = false;
	bool field1[5] = {false, false, false, false, false};
	bool field2[5] = {false, false, false, false, false};
	bool hand1[5] = {true, true, true, true, true};
	bool hand2[5] = {true, true, true, true, true };
	// draw five cards for each hand
	// and put them onto the hand
	while(!gameover)
	{
		while (p1Turn)
		{
			renderWindow.draw(sprite);
			renderWindow.display();
			while (renderWindow.pollEvent(event))
			{
				// game events
			}
		}
		while (p2Turn)
		{
			renderWindow.draw(sprite);
			renderWindow.display();
			while (renderWindow.pollEvent(event))
			{
				// game events
			}
		}
	}


}