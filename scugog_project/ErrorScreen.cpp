#include "stdafx.h"
#include "ErrorScreen.h"

void ErrorScreen::Show(sf::RenderWindow & renderWindow)
{
	//sf::Image image;
	sf::Texture texture;
	if (texture.loadFromFile("../scugog_project/resources/images/error_loading.png") != true)
	{
		return;
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
			if (event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}
