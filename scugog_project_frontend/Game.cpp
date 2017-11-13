//
//  Game.cpp
//  gui
//
//  Created by Akin Shonibare on 2017-10-30.
//  Copyright © 2017 Akin Shonibare. All rights reserved.
//

#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Instructions.h"
#include "ChooseDeck1.h"
#include "ChooseDeck2.h"


void Game::Start(void)
{
    if(_gameState != Uninitialized)
        return;
    
    _mainWindow.create(sf::VideoMode(1024,768,32),"The Game");
    _gameState= Game::ShowingSplash;
    
    while(!IsExiting())
    {
        GameLoop();
    }
    
    _mainWindow.close();
}

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}

void Game::GameLoop()
{
    switch(_gameState)
    {
        case Game::ShowingMenu:
        {
            ShowMenu();
            break;
        }
        case Game::ShowingSplash:
        {
            ShowSplashScreen();
            break;
         }
        case Game::ShowingInstructions:
        {
            ShowInstructions();
            break;
        }
        case Game::ShowingCD1:
        {
            ShowCD1();
            break;
        }
        case Game::ShowingCD2:
        {
            ShowCD2();
            break;
        }
        case Game::Playing:
        {
            sf::Event currentEvent;
            while(_mainWindow.pollEvent(currentEvent))
            {
                _mainWindow.clear(sf::Color(0,0,0));
                //_gameObjectManager.DrawAll(_mainWindow);
                _mainWindow.display();
                    
                    if(currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;
                    
                    if(currentEvent.type == sf::Event::KeyPressed)
                    {
                        if(currentEvent.key.code == sf::Keyboard::Key::Escape) ShowMenu();
                    }
                }
                break;
            }
        }
    
}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    switch(result)
    {
        case MainMenu::Play:
            _gameState = Game::ShowingCD1;
            break;
        case MainMenu::Instruction:
            _gameState = Game::ShowingInstructions;
            break;
        case MainMenu::Exit:
            _gameState = Game::Exiting;
            break;
    }
}


void Game::ShowInstructions()
{
    Instructions instr;
    instr.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowCD1()
{
    ChooseDeck1 cd1;
    cd1.Show(_mainWindow);
    _gameState = Game::ShowingCD2;
}

void Game::ShowCD2()
{
    ChooseDeck2 cd2;
    cd2.Show(_mainWindow);
    _gameState = Game::Playing;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
