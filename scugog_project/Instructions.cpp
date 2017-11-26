#include "stdafx.h"
#include "Instructions.h"



void Instructions::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture texture, card, attackIcon, defenceIcon, costIcon, powerIcon;
	if (texture.loadFromFile("../scugog_project/resources/images/bg.jpg") != true)
	{
		return;
	}
	if (card.loadFromFile("../scugog_project/resources/images/cardExample.png") != true)
	{
		return;
	}

	sf::Sprite sprite(texture);
	renderWindow.draw(sprite);
	sf::Font font;

	sf::Sprite cardSprite(card);
	cardSprite.setPosition(sf::Vector2f(420, 575));
	renderWindow.draw(cardSprite);

	if (!font.loadFromFile("../scugog_project/resources/fonts/sansation.ttf")) {
		return;
	}

	sf::Text text2;
	text2.setFont(font);
	text2.setString("Instructions");
	text2.setCharacterSize(60);
	text2.setFillColor(sf::Color(20, 20, 20));
	text2.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize2 = text2.getGlobalBounds();
	text2.setOrigin(sf::Vector2f(tsize2.width / 2, tsize2.height / 2));
	text2.setPosition(sf::Vector2f(960, 25));

	sf::Text text3;
	text3.setFont(font);
	text3.setString("press 'ENTER' to continue");
	text3.setCharacterSize(30);
	text3.setFillColor(sf::Color(20, 20, 20));
	text3.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize3 = text3.getGlobalBounds();
	text3.setOrigin(sf::Vector2f(tsize3.width / 2, tsize3.height / 2));
	text3.setPosition(sf::Vector2f(960, 80));


	sf::Text instr;
	instr.setFont(font);
	instr.setString("\
		The goal of Food Fight! is to use your cards to lower your opponent's life points to 0 while protecting your life points from the opponent's cards.\n\
		Start the game by clicking on the START! button.\n\
		You will be taken to a page where you will be asked to pick a deck. Pick a deck by clicking on it.\n\
		Once in the game, each player will be given 5 randomly drawn cards from your decks.You will start out with X cost points.\n\
		Place a card on the field by clicking on the card and then on the field.\n\
		Attack an opponent's card by clicking on one of your cards on the field and then on one of the opponent's cards.\n\
		Attack an opponent directly by clicking on one of your cards on the field and then on the opponent's health.\n\
		Cards have 4 attributes: Power, Attack, Defence, and Cost.\n\
		Power determines how many life points your card can take away from the opponent.\n\
		Attack determines how many defence points your card can take away from an oppenent's card.\n\
		Defence determines how many points can be taken from one of your cards by an opponent's card's attack.\n\
		Cost tells you how many cost points it costs to play your card onto the field.\n\
		Some cards have special abilities you can use, play the game to discover them!");
	instr.setCharacterSize(30);
	instr.setFillColor(sf::Color(20, 20, 20));
	instr.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize4 = instr.getGlobalBounds();
	instr.setPosition(sf::Vector2f(-40, 120));

	/*
	Instructions:

	The goal of Food Fight! is to use your cards to lower your opponent's life points to 0 while protecting your life points from the opponent's cards.

	Start the game by clicking on the START! button.

	You will be taken to a page where you will be asked to pick a deck. Pick a deck by clicking on it.

	Once in the game, each player will be given 5 randomly drawn cards from your decks. You will start out with X cost points.

	Place a card on the field by clicking on the card and then on the field.

	Attack an opponent's card by clicking on one of your cards on the field and then on one of the opponent's cards.

	Attack an opponent directly by clicking on one of your cards on the field and then on one of the opponent's cards.

	Cards have 5 attributes: Power, Attack, Defence, Cost, and Ability.

	Power determines how many life points your card can take away from the opponent

	Attack determines how many defence points your card can take away from an oppenent's card

	Defence determines how many points can be taken from one of your cards by an opponent's card's attack

	Cost tells you how many cost points it costs to play your card onto the field

	Some cards have special abilities you can use, play the game to discover them!
	*/


	// cost icon
	if (costIcon.loadFromFile("../scugog_project/resources/images/icons/icon_cost.png") != true)
	{
		return;
	}
	sf::Sprite costSprite(costIcon);
	costSprite.setPosition(sf::Vector2f(750, 592));
	renderWindow.draw(costSprite);

	sf::Text costText;
	costText.setFont(font);
	costText.setString("\
	COST\n\
	Cost to play card on field");
	costText.setCharacterSize(30);
	costText.setFillColor(sf::Color(20, 20, 20));
	costText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize8 = costText.getGlobalBounds();
	costText.setPosition(sf::Vector2f(840, 612));

	// power icon
	if (powerIcon.loadFromFile("../scugog_project/resources/images/icons/icon_power.png") != true)
	{
		return;
	}
	sf::Sprite powerSprite(powerIcon);
	powerSprite.setPosition(sf::Vector2f(750, 702));
	renderWindow.draw(powerSprite);

	sf::Text powerText;
	powerText.setFont(font);
	powerText.setString("\
	POWER\n\
	Damage to your opponent's lifepoints");
	powerText.setCharacterSize(30);
	powerText.setFillColor(sf::Color(20, 20, 20));
	powerText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize5 = powerText.getGlobalBounds();
	powerText.setPosition(sf::Vector2f(840, 722));

	//defence icon
	if (defenceIcon.loadFromFile("../scugog_project/resources/images/icons/icon_defence.png") != true)
	{
		return;
	}
	sf::Sprite defenceSprite(defenceIcon);
	defenceSprite.setPosition(sf::Vector2f(750, 822));
	renderWindow.draw(defenceSprite);

	sf::Text defenceText;
	defenceText.setFont(font);
	defenceText.setString("\
	DEFENCE\n\
	Value taken from opponent's attack");
	defenceText.setCharacterSize(30);
	defenceText.setFillColor(sf::Color(20, 20, 20));
	defenceText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize6 = defenceText.getGlobalBounds();
	defenceText.setPosition(sf::Vector2f(840, 842));

	// attack icon
	if (attackIcon.loadFromFile("../scugog_project/resources/images/icons/icon_attack.png") != true)
	{
		return;
	}
	sf::Sprite attackSprite(attackIcon);
	attackSprite.setPosition(sf::Vector2f(750, 942));
	renderWindow.draw(attackSprite);

	sf::Text attackText;
	attackText.setFont(font);
	attackText.setString("\
	ATTACK\n\
	Value taken from opponent's defence");
	attackText.setCharacterSize(30);
	attackText.setFillColor(sf::Color(20, 20, 20));
	attackText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize7 = attackText.getGlobalBounds();
	attackText.setPosition(sf::Vector2f(840, 962));

	renderWindow.draw(costText);
	renderWindow.draw(powerText);
	renderWindow.draw(defenceText);
	renderWindow.draw(attackText);
	renderWindow.draw(text2);
	renderWindow.draw(text3);
	renderWindow.draw(instr);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}

