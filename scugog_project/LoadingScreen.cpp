#include "stdafx.h"
#include "LoadingScreen.h"

int LoadingScreen::Show(sf::RenderWindow & renderWindow)
{
	//sf::Image image;
	sf::Texture texture;
	if (texture.loadFromFile("../scugog_project/resources/images/loading_screen.jpg") != true)
	{
		return -1;
	}

	//texture.update(image);
	sf::Sprite sprite(texture);
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	renderWindow.pollEvent(event);
	if (event.type == sf::Event::EventType::Closed)
	{
		return -2;
	}

}
