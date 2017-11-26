#include "stdafx.h"
#include "PlayGame.h"

PlayGame::PlayGame() {

}
PlayGame::PlayGame(Environment enviro) {
	env = enviro;
	cardType = -1;
	secondClickType = -1;
	players = enviro.get_players();
	fields = enviro.getField();
}

void PlayGame::Play(sf::RenderWindow & renderWindow)
{
	sf::Texture texture, card, money, texture2, deck1, deck2;
	int deck1Index = players[0].get_deck().get_deck_num();
	int deck2Index = players[1].get_deck().get_deck_num();
	cout << deck1Index << endl;
	cout << deck2Index << endl;
	sf::Font font;
	// load images needed
	if (!font.loadFromFile("../scugog_project/resources/fonts/sansation.ttf")) {
		return;
	}

	if (texture.loadFromFile("../scugog_project/resources/images/bg2.png") != true)
	{
		return;
	}

	if (texture2.loadFromFile("../scugog_project/resources/images/bg.jpg") != true)
	{
		return;
	}

	if (card.loadFromFile("../scugog_project/resources/images/card_pictures/cardc.png") != true)
	{
		return;
	}
	if (money.loadFromFile("../scugog_project/resources/images/money.png") != true)
	{
		return;
	}
	if (deck1Index == 0) {
		if (deck1.loadFromFile("../scugog_project/resources/images/hardy_veggies.png") != true)
		{
			return;
		}
	}
	else {
		if (deck1.loadFromFile("../scugog_project/resources/images/sugar_rush_fruits.png") != true)
		{
			return;
		}
	}

	if (deck2Index == 0) {
		if (deck2.loadFromFile("../scugog_project/resources/images/hardy_veggies.png") != true)
		{
			return;
		}
	}
	else {
		if (deck2.loadFromFile("../scugog_project/resources/images/sugar_rush_fruits.png") != true)
		{
			return;
		}
	}
	// default 
	Card dfltCard(0, 0, 0, 0, 0, 0, "cardc.png", "", "");
	sf::Sprite dflt(card);
	sf::Text dText;
	dText.setString("");
	pair <sf::Sprite, sf::Text> dfltPair;
	dfltPair = make_pair(dflt, dText);

	bool gameover = env.get_game_on();

	sf::Text endTurn;
	endTurn.setFont(font);
	endTurn.setString("End Turn");
	endTurn.setCharacterSize(40);
	endTurn.setFillColor(sf::Color::Black);
	endTurn.setStyle(sf::Text::Style::Italic);
	endTurn.setPosition(sf::Vector2f(1680, 355));

	sf::Text error;
	error.setFont(font);
	error.setString("");
	error.setCharacterSize(30);
	error.setFillColor(sf::Color::Blue);
	error.setStyle(sf::Text::Style::Bold);
	error.setPosition(sf::Vector2f(100, 450));

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
	switchText.setString("Click anywhere when next player is ready");
	switchText.setCharacterSize(85);
	switchText.setFillColor(sf::Color::Blue);
	switchText.setStyle(sf::Text::Style::Italic);
	switchText.setPosition(sf::Vector2f(150, 350));

	sf::Text moneyText;
	moneyText.setFont(font);
	moneyText.setCharacterSize(60);
	moneyText.setFillColor(sf::Color::Black);
	moneyText.setStyle(sf::Text::Style::Italic);
	sf::Sprite sprite_money(money);
	sprite_money.setScale(0.15f, 0.15f);
	sprite_money.setColor(sf::Color::Black);

	sf::Sprite p1Deck(deck1);
	sf::Sprite p2Deck(deck2);

	sf::Sprite sprite(texture);
	sf::Sprite sprite2(texture2);
	
	sf::Event event;

	hand = { dfltPair, dfltPair , dfltPair , dfltPair , dfltPair , dfltPair , dfltPair };
	f1 = { dfltPair , dfltPair , dfltPair , dfltPair , dfltPair };
	f2 = { dfltPair , dfltPair , dfltPair , dfltPair , dfltPair };
	fields[0] = { dfltCard, dfltCard, dfltCard, dfltCard, dfltCard };
	fields[1] = { dfltCard, dfltCard, dfltCard, dfltCard, dfltCard };
	vector<pair<sf::Sprite, sf::Text>> temp;
	h1Full = { true, true, true, true, true, true, false };
	h2Full = { true, true, true, true, true, true, false };
	f1Full = { false, false, false, false, false };
	f2Full = { false, false, false, false, false };
	vector<bool> tempFull;
	int player1Click = 1;
	int player2Click = 2;
	int handCard = 3;
	int fieldCard = 4;
	int indexOne = -1;
	int indexTwo = -1;

	vector<sf::Sprite> clicks;
	vector<Card> cardClicks;
	// need to change these to match indexes later
	int player_turn = env.get_current_player().get_player_number();

	// essentially idea is to place cards as sprites
	// even if they aren't a game card and then use that so
	// that you can click them to move cards and attack
	while (gameover)
	{
		player_turn = env.get_current_player().get_player_number();
		int toReset1 = 0;
		int toReset2 = 0;
		bool player_turn_on = true;
		bool full_deck = true;
		bool start = true; // used to indicate if it is the start of a players turn
		clickable = { true, true, true, true, true };
		while (player_turn_on)
		{

			// intialize hand and field sprites as neccessary depending on who is playing
			if (start) {
				// draw cards at start of turn
				int tempIndex(0);
				for (int i = 0; i < size(h1Full); i++) {
					if (h1Full[i] == false) {
						full_deck = false;
						tempIndex = i;
						break;
					}
				}
				if (full_deck == false) {
					h1Full[tempIndex] = true;
					players[player_turn].draw_card();
				}
				start = false;
			}
			renderWindow.draw(sprite);
			for (int i = 0; i < size(players[player_turn].get_hand()); i++) {
				Card card_from_hand = players[player_turn].get_hand()[i];
				pair <sf::Sprite, sf::Text> card_graphic_pair = card_from_hand.draw_card(300 + 200 * i, 700);
				hand[i] = card_graphic_pair;
				renderWindow.draw(hand[i].first);
				renderWindow.draw(hand[i].second);
			}
			for (int i = 0; i < size(f1); i++) {
				if (env.get_current_player().get_player_number() == 0) {
					Card card_from_field1 = fields[0][i];
					pair <sf::Sprite, sf::Text> card_graphic_pair_f1 = card_from_field1.draw_card(500 + 200 * i, 400);
					f1[i] = card_graphic_pair_f1;
					Card card_from_field2 = fields[1][i];
					pair <sf::Sprite, sf::Text> card_graphic_pair_f2 = card_from_field2.draw_card(500 + 200 * i, 100);
					f2[i] = card_graphic_pair_f2;
					renderWindow.draw(f1[i].first);
					renderWindow.draw(f2[i].first);
					renderWindow.draw(f1[i].second);
					renderWindow.draw(f2[i].second);
				}
				else {
					Card card_from_field1 = fields[1][i];
					pair <sf::Sprite, sf::Text> card_graphic_pair_f1 = card_from_field1.draw_card(500 + 200 * i, 400);
					f1[i] = card_graphic_pair_f1;
					Card card_from_field2 = fields[0][i];
					pair <sf::Sprite, sf::Text> card_graphic_pair_f2 = card_from_field2.draw_card(500 + 200 * i, 100);
					f2[i] = card_graphic_pair_f2;
					renderWindow.draw(f1[i].first);
					renderWindow.draw(f2[i].first);
					renderWindow.draw(f1[i].second);
					renderWindow.draw(f2[i].second);
				}
			}
			renderWindow.draw(endTurn);
			p1Label.setString("Player 1\n" + to_string(players[0].get_hp()));
			p2Label.setString("Player 2\n" + to_string(players[1].get_hp()));
			if (players[player_turn].get_player_number() == 0) { // p1 at bottom, p2 at top
				p1Label.setPosition(sf::Vector2f(80, 470));
				p2Label.setPosition(sf::Vector2f(80, 25));
			}
			else {
				p2Label.setPosition(sf::Vector2f(80, 470));
				p1Label.setPosition(sf::Vector2f(80, 25));
			}

			moneyText.setPosition(sf::Vector2f(120, 600));
			moneyText.setString(to_string(players[player_turn].get_current_resources()));
			sprite_money.setPosition(sf::Vector2f(50, 600));
			if (env.get_current_player().get_player_number() == 0) {
				p1Deck.setPosition(sf::Vector2f(50, 700));
				renderWindow.draw(p1Deck);
			}
			else {
				p2Deck.setPosition(sf::Vector2f(50, 700));
				renderWindow.draw(p2Deck);

			}
			renderWindow.draw(moneyText);
			renderWindow.draw(sprite_money);
			renderWindow.draw(p1Label);
			renderWindow.draw(p2Label);
			renderWindow.draw(error);
			renderWindow.display();
			while (renderWindow.pollEvent(event))
			{
				if (event.type == sf::Event::EventType::MouseButtonPressed) {
					sf::Vector2i mousePos = sf::Mouse::getPosition();
					float horz = mousePos.x;
					float vert = mousePos.y;
					if (inText(endTurn, horz, vert)) {
						player_turn_on = false;
						players[player_turn].set_current_resources(players[player_turn].get_current_resources() + 2);
						env.change_turn();
					}
					if (clicks.empty()) {
						// first "card click event", i.e. who to move to field or attack with
						error.setString("");
						for (int i = 0; i < size(hand); i++) {
							if (inCard(hand[i].first, horz, vert) && h1Full[i]) {
								clicks.push_back(hand[i].first);
								hand[i].first.setColor(sf::Color(0, 255, 0));
								toReset1 = i;
								cardClicks.push_back(players[player_turn].get_hand()[i]);
								cardType = handCard;
								indexOne = i;
							}
						}
						for (int i = 0; i < size(f1); i++) {
							if (inCard(f1[i].first, horz, vert) && f1Full[i]) {
								clicks.push_back(f1[i].first);
								f1[i].first.setColor(sf::Color(0, 255, 0));
								toReset1 = i;
								cardClicks.push_back(fields[player_turn][i]);
								
								
								cardType = fieldCard;
								indexOne = i;
							}
						}
					}
					else if (size(clicks) == 1) {
						// this is the second "card click events" i.e. who to attack
						if (cardType == 3) { //hand card 
							for (int i = 0; i < size(f1); i++) {
								if (inCard(f1[i].first, horz, vert) && !f1Full[i]) {
									secondClickType = fieldCard;
									f1[i].first.setColor(sf::Color(0, 255, 0));
									toReset2 = i;
									indexTwo = i;
								}
							}
							//*************************************************************************************************************************************************************************************//
							if (inGrave(horz, vert)) {
								secondClickType = 5;
							}
							//*************************************************************************************************************************************************************************************//

						}
						else {
							for (int i = 0; i < size(f2); i++) {
								if (inCard(f2[i].first, horz, vert) && f2Full[i]) {
									clicks.push_back(f2[i].first);
									f2[i].first.setColor(sf::Color(255, 0, 0));
									toReset2 = i;
									cardClicks.push_back(fields[(player_turn + 1) % 2][i]);
									secondClickType = fieldCard;
									indexTwo = i;
								}
							}
							//*************************************************************************************************************************************************************************************//
							if (inGrave(horz, vert)) {
								secondClickType = 5;
							}
							//*************************************************************************************************************************************************************************************//
							
							if (players[player_turn].get_player_number() == 0) {
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
						int worked = handleClicks(clicks, cardClicks, indexOne, indexTwo);
						error.setString(handleError(worked));
						//reset the colour of any clicked sprites
						hand[toReset1].first.setColor(sf::Color(255, 255, 255));
						f1[toReset1].first.setColor(sf::Color(255, 255, 255));
						f1[toReset2].first.setColor(sf::Color(255, 255, 255));
						f2[toReset2].first.setColor(sf::Color(255, 255, 255));
						// and the end of this need to clear the "clicks" vector
						clicks.clear();
						cardClicks.clear();
						// and set selectors back to -1 when done
						cardType = -1;
						secondClickType = -1;
						indexOne = -1;
						indexTwo = -1;
					}

				}

				if (event.type == sf::Event::Closed) {
					return;
				}
			}
			start = false;
			if (players[0].get_hp() <= 0 || players[1].get_hp() <= 0) {
				env.end_game();
				gameover = env.get_game_on();

			}
		}
		// intiate waiting screen with switching of player sprites
		bool switching = true;
		while (switching) {
			renderWindow.draw(sprite2);
			renderWindow.draw(switchText);
			renderWindow.display();
			while (renderWindow.pollEvent(event)) {
				if (event.type == sf::Event::EventType::MouseButtonPressed) {
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
		tempFull = f1Full;
		f1Full = f2Full;
		f2Full = tempFull;
		tempFull = h1Full;
		h1Full = h2Full;
		h2Full = tempFull;
		// swap to new hand
		// TODO: figure out how card sprites are working
		//for (int i = 0; i < size(hand); i++) {
		//hand[i] = env.get_current_player().get_hand()[i].;
		//}
		
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

//*************************************************************************************************************************************************************************************//

bool PlayGame::inGrave(float mpx, float mpy) {
	cout << mpx << " " << mpy << endl;
	if ((mpx < 1838) && (mpx > 1682) && (mpy < 671) && (mpy > 496)) {
		return true;
	}
	return false;
}
//*************************************************************************************************************************************************************************************//


int PlayGame::handleClicks(vector<sf::Sprite> clicks, vector<Card> cardClicks, int indexOne, int indexTwo) {
	if (cardType == 4) {
		if (!clickable[indexOne]) {
			return 1;
		}
	}
	if (secondClickType == 4) {
		if (!clickable[indexTwo]) {
			return 1;
		}
	}
	// 1 = player 1
	// 2 = player 2
	// 3 = hand card
	// 4 = field card
	// 5 = clicked on grave
	// -1 = no clic
	sf::Texture card;
	// load images needed for default
	if (card.loadFromFile("../scugog_project/resources/images/cardcc.png") != true)
	{
		return -2;
	}
	// default 
	int player_turn = env.get_current_player().get_player_number();
	Card dfltCard(0, 0, 0, 0, 0, 0, "cardc.png", "", "");
	sf::Sprite dflt(card);
	sf::Text dText;
	dText.setString("");
	pair <sf::Sprite, sf::Text> dfltPair;
	dfltPair = make_pair(dflt, dText);
	//if no valid click for second object exit
	if (secondClickType == -1) {
		return 0;
	}

	//if moving a card from hand to field
	else if ((cardType == 3) && (secondClickType == 4)) {
		if (f1Full[indexTwo] || !h1Full[indexOne] || !clickable[indexTwo]) {
			return 1;
		}
		if (cardClicks[0].get_cost() <= players[player_turn].get_current_resources()) {
			pair<sf::Sprite, sf::Text> pair = cardClicks[0].draw_card(0, 0);
			f1[indexTwo] = pair;
			f1Full[indexTwo] = true;
			fields[player_turn][indexTwo] = cardClicks[0];
			for (int i = 0; i < size(hand); i++) {
				if (h1Full[i] == false) {
					h1Full[i - 1] = false;
				}
				else if (i == size(hand) - 1) {
					h1Full[6] = false;
				}
			}
			fields[player_turn][indexTwo] = players[player_turn].remove_card_from_hand(indexOne);
			players[player_turn].set_current_resources(players[player_turn].get_current_resources() - cardClicks[0].get_cost());
			clickable[indexTwo] = false;
		}
		else {
			return -1;
		}
	}
	//if attacking another card
	//if attacking another card
	else if ((cardType == 4) && (secondClickType == 4)) {
		clickable[indexOne] = false;
		cout << "attacking card" << endl;
		//get attack and defense values
		int opponent_defense = cardClicks[1].get_defense();
		int opponent_attack = cardClicks[1].get_attack();
		int player_defense = cardClicks[0].get_defense();
		int player_attack = cardClicks[0].get_attack();
		cout << "cClicks size: " << size(cardClicks) << endl;
		cout << "Player Def " << player_defense << endl;
		cout << "Opponent Def " << opponent_defense << endl;
		cout << "Player Atk " << player_attack << endl;
		cout << "Opponent Atk " << opponent_attack << endl;
		cardClicks[1].set_defense(opponent_defense - player_attack);
		//cardClicks[0].set_defense(player_defense - opponent_attack);

		cout << "Player Def " << cardClicks[1].get_defense() << endl;
		cout << "Opponent Def " << cardClicks[0].get_defense() << endl;
		if (cardClicks[1].get_defense() <= 0) {
			// enemy died
			fields[(player_turn + 1) % 2][indexTwo] = dfltCard;
			f2[indexTwo] = dfltPair;
			f2Full[indexTwo] = false;
		}
		else {
			//enemy didn't die
			fields[(player_turn + 1) % 2][indexTwo] = cardClicks[1];
			f2[indexTwo] = fields[(player_turn + 1) % 2][indexTwo].draw_card(0,0);
			f2Full[indexTwo] = true;
		}
		// making it so nothing happens to you when you attack
		/*if (cardClicks[0].get_defense() <= 0) {
			// you died
			fields[player_turn][indexOne] = dfltCard;
			f1[indexOne] = dfltPair;
			f1Full[indexOne] = false;
		}
		else {
			// you didn't die
			fields[player_turn][indexOne] = cardClicks[0];
			f1[indexOne] = fields[player_turn][indexOne].draw_card(0, 0);
			f1Full[indexOne] = true;
		}*/
		//if both cards kill each other
		/*if ((opponent_defense - player_attack <= 0) && (player_defense - opponent_attack <= 0)) {
			cout << "both dead" << endl;
			f2[indexTwo] = dfltPair;
			f2Full[indexTwo] = false;
			f1[indexOne] = dfltPair;
			f1Full[indexOne] = false;
			fields[player_turn][indexOne] = dfltCard;
			fields[(player_turn + 1) % 2][indexTwo] = dfltCard;
		}
		//if you kill the opponent card
		else if (opponent_defense - player_attack <= 0) {
			cout << "opponent dead" << endl;
			//remove_card_from_field(((player_turn + 1) % 2), indexTwo);
			cardClicks[1].set_defense(player_defense - opponent_attack);
			f2[indexTwo] = dfltPair;
			f2Full[indexTwo] = false;
			fields[(player_turn + 1) % 2][indexTwo] = dfltCard;
			fields[player_turn][indexOne] = cardClicks[1];
		}
		//if you kill your own card
		else if (player_defense - opponent_attack <= 0) {
			cout << "you dead" << endl;
			//remove_card_from_field(player_turn, indexTwo);
			cardClicks[0].set_defense(opponent_defense - player_attack);
			f1[indexOne] = dfltPair;
			f1Full[indexOne] = false;
			fields[player_turn][indexOne] = dfltCard;
			fields[(player_turn + 1) % 2][indexTwo] = cardClicks[0];
		}
		//you do damage to both cards
		else
		{
			cardClicks[1].set_defense(player_defense - opponent_attack);
			cardClicks[0].set_defense(opponent_defense - player_attack);
			fields[player_turn][indexOne] = cardClicks[1];
			fields[(player_turn + 1) % 2][indexTwo] = cardClicks[0];
		}*/

	}
	//if you attack the player
	else if ((secondClickType == 1) || (secondClickType == 2)) {
		if (!clickable[indexOne]) {
			return 1;
		}
		int toAttack = cardClicks[0].get_power();
		int currenthp = players[(player_turn + 1) % 2].get_hp();
		players[(player_turn + 1) % 2].set_hp(currenthp - toAttack);
		clickable[indexOne] = false;
	}
	//*************************************************************************************************************************************************************************************//
	else if ((cardType == 4) && (secondClickType == 5) && clickable[indexOne]) {
		fields[player_turn][indexOne] = dfltCard;
		f1[indexOne] = dfltPair;
		f1Full[indexOne] = false;
		players[player_turn].set_current_resources(players[player_turn].get_current_resources() + 1);
	}
	//*************************************************************************************************************************************************************************************//
	//*************************************************************************************************************************************************************************************//
	else if ((cardType == 3) && (secondClickType == 5) && clickable[indexOne]) {
		Card tempCard = players[player_turn].remove_card_from_hand(indexOne);
		players[player_turn].set_current_resources(players[player_turn].get_current_resources() + 1);
		f1Full[indexOne] = false;
		for (int i = 0; i < size(hand); i++) {
			if (h1Full[i] == false) {
				h1Full[i - 1] = false;
			}
			else if (i == size(hand) - 1) {
				h1Full[6] = false;
			}
		}
	}
	//*************************************************************************************************************************************************************************************//


	//if you killed the opponent
	if (players[(player_turn + 1) % 2].get_hp() <= 0) {
		env.end_game();
	}

	return 3;
}

string PlayGame::handleError(int worked) {
	// -2 = no default card
	// -1 = not enough resources
	// 0 = no second card clicked
	// 1 = illegal move
	// 2 =
	// 3 = all good
	if (worked == -2) {
		return "no default card";
	}
	else if (worked == -1) {
		return "not enough resources";
	}
	else if (worked == 0) {
		return "no second card clicked";
	}
	else if (worked == 1) {
		return "illegal move";
	}
	else if (worked == 2) {
		return "";
	}
	else if (worked == 3) {
		return "";
	}
	else if (worked == 4) {
		return "double clicked card";
	}
	return "unknown error";
}

//Environment PlayGame::getEnvironment() {
//return env;
//}