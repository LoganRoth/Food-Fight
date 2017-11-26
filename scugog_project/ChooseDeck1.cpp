#include "stdafx.h"
#include "ChooseDeck1.h"



int ChooseDeck1::Show(sf::RenderWindow & renderWindow)
{
    
    sf::Texture texture, card1, card2;
    sf::Font font;
    if (!font.loadFromFile("../scugog_project/resources/fonts/sansation.ttf")) {
        return -1;
    }
    
    if(texture.loadFromFile("../scugog_project/resources/images/bg.jpg") != true)
    {
        return -1;
    }
    
    if(card1.loadFromFile("../scugog_project/resources/images/hardy_veggies.png") != true)
    {
        return -1;
    }
	if (card2.loadFromFile("../scugog_project/resources/images/sugar_rush_fruits.png") != true)
	{
		return -1;
	}
   
    sf::Sprite cd1(card1);
    sf::Sprite cd2(card2);
	

    
    sf::Text text;
    text.setFont(font);
    text.setString("press 'Enter' when player 1 has chosen deck");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Style::Italic);
    sf::Rect<float> tsize = text.getGlobalBounds();
    text.setOrigin(sf::Vector2f(tsize.width/2, tsize.height/2));
    text.setPosition(sf::Vector2f(960, 25));

	sf::Text deckDone;
	deckDone.setFont(font);
	deckDone.setString("");
	deckDone.setCharacterSize(30);
	deckDone.setFillColor(sf::Color::Black);
	deckDone.setStyle(sf::Text::Style::Regular);
	sf::Rect<float> dDsize = deckDone.getGlobalBounds();
	deckDone.setOrigin(sf::Vector2f(dDsize.width / 2, dDsize.height / 2));
	deckDone.setPosition(sf::Vector2f(960, 550));
    
    cd1.setOrigin(sf::Vector2f(106, 150));
    cd2.setOrigin(sf::Vector2f(106, 150));
    
    cd1.setPosition(sf::Vector2f(960 -125 , 350));
    cd2.setPosition(sf::Vector2f(960 + 125, 350));
	sf::FloatRect cd1Pos = cd1.getGlobalBounds();
	sf::FloatRect cd2Pos = cd2.getGlobalBounds();
	float cd1L = cd1Pos.left;
	float cd1R = cd1Pos.left + cd1Pos.width;
	float cd1T = cd1Pos.top;
	float cd1B = cd1Pos.top + cd1Pos.height;
	float cd2L = cd2Pos.left;
	float cd2R = cd2Pos.left + cd2Pos.width;
	float cd2T = cd2Pos.top;
	float cd2B = cd2Pos.top + cd2Pos.height;
    
    
    //texture.update(image);
    sf::Sprite sprite(texture);
    
    sf::Event event;
	int deckChoice = -1;
    while(true)
    {
		renderWindow.draw(sprite);
		renderWindow.draw(text);
		renderWindow.draw(cd1);
		renderWindow.draw(cd2);
		renderWindow.draw(deckDone);
		renderWindow.display();
        while(renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::EventType::KeyPressed)
            {
				if (deckChoice == -1) {
					deckDone.setString("No Deck Chosen!");
					deckDone.setPosition(sf::Vector2f(825, 550));
				}
				else {
					return deckChoice;
				}
            }
			if (event.type == sf::Event::EventType::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition();
				float horz = mousePos.x;
				float vert = mousePos.y;
				if ((horz > cd1L) && (horz < cd1R) && (vert > cd1T) && (vert < cd1B)) {
					deckChoice = 0;
					deckDone.setString("Hardy Veggies Chosen!");
					deckDone.setPosition(sf::Vector2f(800, 550));
				}
				else if ((horz > cd2L) && (horz < cd2R) && (vert > cd2T) && (vert < cd2B)) {
					deckChoice = 1;
					deckDone.setString("Sugar Rush Fruits Chosen!");
					deckDone.setPosition(sf::Vector2f(785, 550));
				}
				else {
					deckChoice = -1;
					deckDone.setString("");
				}
			}
			if (event.type == sf::Event::Closed) {
				return -1;
			}
        }
    }
}

