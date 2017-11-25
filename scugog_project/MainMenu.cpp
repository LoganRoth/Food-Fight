#include "stdafx.h"
#include "MainMenu.h"
#include <iostream>

using namespace std;


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	sf::Vector2u WindowSize;
	WindowSize = window.getSize();
    sf::Texture texture;
    texture.loadFromFile("../scugog_project/resources/images/mm.jpg");
    sf::Sprite sprite(texture);
	sf::Vector2u SpriteSize;
   
    //Setup clickable regions
    
    //Play menu item coordinates
    MenuItem playButton;
    playButton.rect.top= 1;
    playButton.rect.height = WindowSize.y/3;
    playButton.rect.left = 1;
    playButton.rect.width = WindowSize.x;
    playButton.action = Play;
    
    //Play instructionButton item coordinates
    MenuItem instructionButton;
    instructionButton.rect.top= WindowSize.y/3;
	instructionButton.rect.height = WindowSize.y/3;
	instructionButton.rect.left = 1;
	instructionButton.rect.width = WindowSize.x;
    instructionButton.action = Instruction;
    
    //Exit menu item coordinates
    MenuItem exitButton;
    exitButton.rect.left = 1;
    exitButton.rect.width = WindowSize.x;
    exitButton.rect.top = WindowSize.y / 3 * 2;
    exitButton.rect.height = WindowSize.y /3;
    exitButton.action = Exit;
    
    _menuItems.push_back(playButton);
    _menuItems.push_back(instructionButton);
    _menuItems.push_back(exitButton);
    
    window.draw(sprite);
    window.display();
    
    return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;
    
    for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        sf::Rect<int> menuItemRect = (*it).rect;
        if( (menuItemRect.height + menuItemRect.top) > y && menuItemRect.top < y && menuItemRect.left < x && (menuItemRect.left + menuItemRect.width) > x)
        {
            return (*it).action;
            //std::cout << (*it).action << std::endl;
        }
    }
    
    return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event menuEvent;
    
    while(true)
    {
        while(window.pollEvent(menuEvent))
        {
            if(menuEvent.type == sf::Event::MouseButtonPressed)
            {
                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            }
            if(menuEvent.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}
