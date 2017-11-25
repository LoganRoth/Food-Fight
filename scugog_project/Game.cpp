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
#include "PlayGame.h"




void Game::Start(void)
{
    if(_gameState != Uninitialized)
        return;
    
    _mainWindow.create(sf::VideoMode(1920,1080,64),"The Game", sf::Style::Titlebar | sf::Style::Close);
    _gameState= Game::ShowingSplash;

	GameLoop();
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
	int deck1 = 1;
	int deck2 = 1;
	while (_gameState != Game::Exiting) {
		vector<int> decks = { deck1, deck2 };
		switch (_gameState)
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
				deck1 = ShowCD1();
				if (deck1 == -1) {
					_gameState = Game::Exiting;
				}
				else {
					_gameState = Game::ShowingCD2;
				}
				break;
			}
			case Game::ShowingCD2:
			{
				deck2 = ShowCD2();
				if (deck2 == -1) {
					_gameState = Game::Exiting;
				}
				else {
					_gameState = Game::Playing;
				}
				break;
			}
			case Game::Playing:
			{
				// TODO: Backend Integration gives a "cannot open source file error"
				Environment env(2, decks);
				Game::ActivateGame(env);
			}
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

int Game::ShowCD1()
{
    ChooseDeck1 cd1;
    int deckN = cd1.Show(_mainWindow);
	return deckN;
}

int Game::ShowCD2()
{
    ChooseDeck2 cd2;
    int deckN = cd2.Show(_mainWindow);
	return deckN;
}
// TODO: This function will have the actual "playing of the game"
void Game::ActivateGame(Environment env) 
{
	PlayGame gm(env);
	gm.Play(_mainWindow);
	// need to handle game exiting somehow
	_gameState = Game::Exiting;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;