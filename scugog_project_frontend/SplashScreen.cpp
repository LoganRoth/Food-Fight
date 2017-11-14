#include "stdafx.h"
#include "SplashScreen.h"



void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
    //sf::Image image;
    sf::Texture texture;
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return;
    }
    
    if(texture.loadFromFile("play.jpg") != true)
    {
       return;
    }
    
    sf::Text text;
    text.setFont(font);
    text.setString("FARM BOUT");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Style::Italic);
    sf::Rect<float> tsize = text.getGlobalBounds();
    text.setOrigin(sf::Vector2f(tsize.width/2, tsize.height/2));
    text.setPosition(sf::Vector2f(512, 300));
    
    //texture.update(image);
    sf::Sprite sprite(texture);
    
    renderWindow.draw(sprite);
    renderWindow.draw(text);
    renderWindow.display();
    
    sf::Event event;
    while(true)
    {
        while(renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::EventType::MouseButtonPressed
               || event.type == sf::Event::EventType::Closed )
            {
                return;
             }
         }
    }
}
