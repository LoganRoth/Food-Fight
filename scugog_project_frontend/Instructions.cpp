#include "stdafx.h"
#include "Instructions.h"



void Instructions::Show(sf::RenderWindow & renderWindow)
{
    sf::Texture texture;
 /*   if(texture.loadFromFile(resourcePath() + "bg.jpg") != true)
    {
        return;
    }*/
    
    sf::Sprite sprite(texture);
    renderWindow.draw(sprite);
    sf::Font font;
    
  /*  if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return;
    }
    */
    sf::Text text2;
    text2.setFont(font);
    text2.setString("instructions");
    text2.setCharacterSize(60);
    text2.setFillColor(sf::Color(128,128,128));
    text2.setStyle(sf::Text::Style::Italic);
    sf::Rect<float> tsize2 = text2.getGlobalBounds();
    text2.setOrigin(sf::Vector2f(tsize2.width/2, tsize2.height/2));
    text2.setPosition(sf::Vector2f(512, 25));
    
    sf::Text text3;
    text3.setFont(font);
    text3.setString("press 'ENTER' to contunue");
    text3.setCharacterSize(30);
    text3.setFillColor(sf::Color(128,128,128));
    text3.setStyle(sf::Text::Style::Italic);
    sf::Rect<float> tsize3 = text3.getGlobalBounds();
    text3.setOrigin(sf::Vector2f(tsize3.width/2, tsize3.height/2));
    text3.setPosition(sf::Vector2f(512, 80));
    
    renderWindow.draw(text2);
    renderWindow.draw(text3);
    renderWindow.display();
    
    sf::Event event;
    while(true)
    {
        while(renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::Closed)
            {
                return;
            }
        }
    }
}

