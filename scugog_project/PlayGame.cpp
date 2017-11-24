#include "stdafx.h"
#include "PlayGame.h"

void PlayGame::Play(Environment env, sf::RenderWindow & renderWindow) 
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
	vector<Player> players = env.get_players();
	bool gameover = env.get_game_on();
	Player player_turn = env.get_current_player();
	vector<Card> field1;
	vector<Card> field2;

	// draw five cards for each hand
	// and put them onto the hand
	while (gameover)
	{
		bool player_turn_on = true;
		while (player_turn_on)
		{	
			renderWindow.draw(sprite);
			for (int i = 0; i < size(player_turn.get_hand()); i++) {
				sf::Sprite cd(card);
				cd.setOrigin(sf::Vector2f(106, 150));
				cd.setPosition(sf::Vector2f(960 + 200 * i, 350));
				renderWindow.draw(cd);
			}
			sf::Text text;
			text.setFont(font);
			text.setString("End Turn");
			text.setCharacterSize(50);
			text.setFillColor(sf::Color::Blue);
			text.setStyle(sf::Text::Style::Italic);
			sf::Rect<float> tsize = text.getGlobalBounds();
			text.setOrigin(sf::Vector2f(tsize.width / 2, tsize.height / 2));
			text.setPosition(sf::Vector2f(960, 25));

			float cd1L = tsize.left;
			float cd1R = tsize.left + tsize.width;
			float cd1T = tsize.top;
			float cd1B = tsize.top + tsize.height;
			renderWindow.draw(text);

			renderWindow.display();
			while (renderWindow.pollEvent(event))
			{
				if (event.type == sf::Event::EventType::MouseButtonPressed) {
					sf::Vector2i mousePos = sf::Mouse::getPosition();
					float horz = mousePos.x;
					float vert = mousePos.y;
					if ((horz > cd1L) && (horz < cd1R) && (vert > cd1T) && (vert < cd1B)) {
						player_turn_on = false;
						env.change_turn();
						cout << env.get_current_player().get_player_number() << endl;
					}
				}
			}
		}
		if (players[0].get_hp() == 0 || players[1].get_hp() == 0) {
			env.end_game();
		}
	}

}