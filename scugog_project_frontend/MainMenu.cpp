#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    sf::Texture texture;
    //texture.loadFromFile(resourcePath() + "mm.png");
    sf::Sprite sprite(texture);
   
    //Setup clickable regions
    
    //Play menu item coordinates
    MenuItem playButton;
    playButton.rect.top= 1;
    playButton.rect.height = 255;
    playButton.rect.left = 1;
    playButton.rect.width = 1023;
    playButton.action = Play;
    
    //Play instructionButton item coordinates
    MenuItem instructionButton;
    instructionButton.rect.top= 256;
    instructionButton.rect.height = 255;
    instructionButton.rect.left = 0;
    instructionButton.rect.width = 1023;
    instructionButton.action = Instruction;
    
    //Exit menu item coordinates
    MenuItem exitButton;
    exitButton.rect.left = 0;
    exitButton.rect.width = 1023;
    exitButton.rect.top = 512;
    exitButton.rect.height = 256;
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
