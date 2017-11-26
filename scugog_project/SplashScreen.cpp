#include "stdafx.h"
#include "SplashScreen.h"

int SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	//sf::Image image;
	sf::Texture texture;
	if (texture.loadFromFile("../scugog_project/resources/images/splash_screen2.png") != true)
	{
		return -1;
	}

	//texture.update(image);
	sf::Sprite sprite(texture);
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				return -2;
			}
			else if (event.type == sf::Event::EventType::MouseButtonPressed) {
				return 0;
			}
		}
	}
}
