#include "stdafx.h"
#include "PlayGame.h"

PlayGame::PlayGame() {

}
PlayGame::PlayGame(Environment enviro) {
	env = enviro;
	cardType = -1;
	secondClickType = -1;
}

void PlayGame::Play(sf::RenderWindow & renderWindow) 
{
	sf::Texture texture, card;
	sf::Font font;
	// load images needed
	if (!font.loadFromFile("../scugog_project/resources/fonts/sansation.ttf")) {
		return;
	}

	if (texture.loadFromFile("../scugog_project/resources/images/bg.jpg") != true)
	{
		return;
	}

	if (card.loadFromFile("../scugog_project/resources/images/cardc.png") != true)
	{
		return;
	}
	// default 
	sf::Sprite dflt(card);

	vector<Player> players = env.get_players();
	bool gameover = env.get_game_on();
	Player player_turn = env.get_current_player();

	sf::Text endTurn;
	endTurn.setFont(font);
	endTurn.setString("End Turn");
	endTurn.setCharacterSize(50);
	endTurn.setFillColor(sf::Color::Blue);
	endTurn.setStyle(sf::Text::Style::Italic);
	endTurn.setPosition(sf::Vector2f(900, 25));

	sf::Text p1Label;
	p1Label.setFont(font);
	p1Label.setCharacterSize(50);
	p1Label.setFillColor(sf::Color::Blue);
	p1Label.setStyle(sf::Text::Style::Italic);
	

	sf::Text p2Label;
	p2Label.setFont(font);
	p2Label.setCharacterSize(50);
	p2Label.setFillColor(sf::Color::Blue);
	p2Label.setStyle(sf::Text::Style::Italic);

	sf::Text switchText;
	switchText.setFont(font);
	switchText.setString("Press a key when next player is ready");
	switchText.setCharacterSize(100);
	switchText.setFillColor(sf::Color::Blue);
	switchText.setStyle(sf::Text::Style::Italic);
	switchText.setPosition(sf::Vector2f(150, 300));
	

	sf::Sprite sprite(texture);

	sf::Event event;
	

	hand = { dflt, dflt ,dflt ,dflt ,dflt ,dflt ,dflt };
	f1 = { dflt ,dflt ,dflt ,dflt ,dflt };
	f2 = { dflt ,dflt ,dflt ,dflt ,dflt };
	vector<sf::Sprite> temp;
	h1Full = {true, true, true, true, true, true, false};
	h2Full = {true, true, true, true, true, true, false};
	f1Full = {false, false, false, false, false};
	f2Full = {false, false, false, false, false};
	int player1Click = 1;
	int player2Click = 2;
	int handCard = 3;
	int fieldCard = 4;

	vector<sf::Sprite> clicks;
	vector<Card> cardClicks;
	// need to change these to match indexes later
	vector<Card> field1;
	vector<Card> field2;
	Player cPlayer;

	// draw five cards for each hand
	// and put them onto the hand

	// essentially idea is to place cards as sprites
	// even if they aren't a game card and then use that so
	// that you can click them to move cards and attack
	while (gameover)
	{
		int toReset1(0);
		int toReset2(0);
		bool player_turn_on = true;
		bool start = true; // used to indicate if it is the start of a players turn
		cPlayer = env.get_current_player();
		while (player_turn_on)
		{	
			// intialize hand and field sprites as neccessary depending on who is playing
			if (start) {
				// draw cards at start of turn, how many?
				start = false;
			}
			renderWindow.draw(sprite);
			for (int i = 0; i < 7 /*size(player_turn.get_hand())*/; i++) {
				hand[i].setPosition(sf::Vector2f(300 + 200 * i, 700));
				renderWindow.draw(hand[i]);
			}
			for (int i = 0; i < size(f1); i++) {
				f1[i].setPosition(sf::Vector2f(500 + 200 * i, 400));
				f2[i].setPosition(sf::Vector2f(500 + 200 * i, 100));
				renderWindow.draw(f1[i]);
				renderWindow.draw(f2[i]);
			}
			renderWindow.draw(endTurn);
			p1Label.setString("Player 1\n" + to_string(players[0].get_hp()));
			p2Label.setString("Player 2\n" + to_string(players[1].get_hp()));
			if (cPlayer.get_player_number() == 0) { // p1 at bottom, p2 at top
				p1Label.setPosition(sf::Vector2f(100, 900));
				p2Label.setPosition(sf::Vector2f(100, 25));
			}
			else {
				p2Label.setPosition(sf::Vector2f(100, 900));
				p1Label.setPosition(sf::Vector2f(100, 25));
			}
			renderWindow.draw(p1Label);
			renderWindow.draw(p2Label);
			renderWindow.display();
			while (renderWindow.pollEvent(event))
			{
				if (event.type == sf::Event::EventType::MouseButtonPressed) {
					sf::Vector2i mousePos = sf::Mouse::getPosition();
					float horz = mousePos.x;
					float vert = mousePos.y;
					if (inText(endTurn, horz, vert)) {
						player_turn_on = false;
						env.change_turn();
					}
					if (clicks.empty()) {
						// first "card click event", i.e. who to move to field or attack with
						for (int i = 0; i < size(hand); i++) {
							if (inCard(hand[i], horz, vert) && h1Full[i]) {
								clicks.push_back(hand[i]);
								hand[i].setColor(sf::Color(0, 255, 0));
								toReset1 = i;
								cardClicks.push_back(cPlayer.get_hand()[i]);
								cardType = handCard;
							}
						}
						for (int i = 0; i < size(f1);i++) {
							if (inCard(f1[i], horz, vert) && f1Full[i]) {
								clicks.push_back(f1[i]);
								f1[i].setColor(sf::Color(0, 255, 0));
								toReset1 = i;
								if (cPlayer.get_player_number() == 0) {
									cardClicks.push_back(env.getField()[0][i]);
								}
								else {
									cardClicks.push_back(env.getField()[1][i]);
								}
								cardType = fieldCard;
							}
						}
					}
					else if (size(clicks) == 1) {
						// this is the second "card click events" i.e. who to attack
						if (cardType == 3) { //hand card 
							for (int i = 0; i < size(f1); i++) {
								if (inCard(f1[i], horz, vert) && !f1Full[i]) {
									secondClickType = fieldCard;
									f1[i].setColor(sf::Color(0, 255, 0));
									toReset2 = i;
								}
							}
						}
						else {
							for (int i = 0; i < size(f2); i++) {
								if (inCard(f2[i],horz,vert) && f2Full[i]){
									clicks.push_back(f2[i]);
									f2[i].setColor(sf::Color(255, 0, 0));
									toReset2 = i;
									if (cPlayer.get_player_number() == 0) {
										cardClicks.push_back(env.getField()[0][i]);
									}
									else {
										cardClicks.push_back(env.getField()[1][i]);
									}
									secondClickType = fieldCard;
								}
								
							}
							if (cPlayer.get_player_number() == 0) {
								if (inText(p2Label, horz, vert)) {
									secondClickType = player2Click;
								}
							}
							else {
								if (inText(p1Label, horz, vert)) {
									secondClickType = player1Click;
								}
							}
						}
						//handle the cards clicked
						handleClicks(clicks, cardClicks);
						//reset the colour of any clicked sprites
						hand[toReset1].setColor(sf::Color(255, 255, 255));
						f1[toReset1].setColor(sf::Color(255, 255, 255));
						f1[toReset2].setColor(sf::Color(255, 255, 255));
						f2[toReset2].setColor(sf::Color(255, 255, 255));
						// and the end of this need to clear the "clicks" vector
						clicks.clear();
						cardClicks.clear();
						// and set selectors back to -1 when done
						cardType = -1;
						secondClickType = -1;
					}
					
				}

				if (event.type == sf::Event::Closed) {
					return;
				}
			}
			start++;
		}
		// intiate waiting screen with switching of player sprites
		bool switching = true;
		while (switching) {
			renderWindow.draw(sprite);
			renderWindow.draw(switchText);
			renderWindow.display();
			while (renderWindow.pollEvent(event)) {
				if (event.type == sf::Event::EventType::KeyPressed) {
					switching = false;
				}
				if (event.type == sf::Event::Closed) {
					return;
				}
			}
		}
		// swapping fields
		temp = f1;
		f1 = f2;
		f2 = temp;
		// swap to new hand
		// TODO: figure out how card sprites are working
		//for (int i = 0; i < size(hand); i++) {
			//hand[i] = env.get_current_player().get_hand()[i].;
		//}
		if (players[0].get_hp() <= 0 || players[1].get_hp() <= 0) {
			env.end_game();
			gameover = env.get_game_on();
		}
	}

}

bool PlayGame::inCard(sf::Sprite crd, float mpx, float mpy)
{
	sf::Rect<float> csize = crd.getGlobalBounds();
	float cd1L = csize.left;
	float cd1R = csize.left + csize.width;
	float cd1T = csize.top;
	float cd1B = csize.top + csize.height;
	if ((mpx > cd1L) && (mpx < cd1R) && (mpy > cd1T) && (mpy < cd1B)) {
		return true;
	}
	return false;
}

bool PlayGame::inText(sf::Text text, float mpx, float mpy)
{
	sf::Rect<float> tsize = text.getGlobalBounds();
	float cd1L = tsize.left;
	float cd1R = tsize.left + tsize.width;
	float cd1T = tsize.top;
	float cd1B = tsize.top + tsize.height + 70;
	if ((mpx > cd1L) && (mpx < cd1R) && (mpy > cd1T) && (mpy < cd1B)) {
		return true;
	}
	return false;
}

void PlayGame::handleClicks(vector<sf::Sprite> clicks, vector<Card> cardClicks) {
	// 1 = player 1
	// 2 = player 2
	// 3 = hand card
	// 4 = field card
	// -1 = no click

	int toAttack(0);

	//get amount to attack with
	if (cardType == 4) {
		toAttack = cardClicks[0].get_attack();
	}

	//if chose to attack player 1
	if (secondClickType == 1 || secondClickType == 2) {
		int currenthp = env.get_current_opponent().get_hp();
		cout << "Current " << currenthp << " Attack " << toAttack << endl;
		env.get_current_opponent().set_hp(currenthp - toAttack);
	}
	
}

//Environment PlayGame::getEnvironment() {
	//return env;
//}