#include "stdafx.h"
#include "LoadingScreen.h"

int LoadingScreen::Show(sf::RenderWindow & renderWindow)
{
	//sf::Image image;
	sf::Texture texture;
	sf::Font font;
	if (!font.loadFromFile("../scugog_project/resources/fonts/BerlinSansFBDemiBold.ttf")) {
		return -1;
	}
	if (texture.loadFromFile("../scugog_project/resources/images/loading_screen.jpg") != true)
	{
		return -1;
	}

	sf::Vector2u windowSize = renderWindow.getSize();
	sf::Text text;
	text.setFont(font);
	text.setString("It's early in the morning, We are still setting up your fields");
	text.setCharacterSize(60);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize = text.getGlobalBounds();
	text.setPosition(sf::Vector2f(windowSize.x - tsize.width - 75, 100));

	//texture.update(image);
	sf::Sprite sprite(texture);
	renderWindow.draw(sprite);
	renderWindow.draw(text);
	renderWindow.display();

	sf::Event event;
	renderWindow.pollEvent(event);
	if (event.type == sf::Event::EventType::Closed)
	{
		return -2;
	}

}
