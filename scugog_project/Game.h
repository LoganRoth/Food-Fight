//
//  Game.h
//  gui
//
//  Created by Akin Shonibare on 2017-10-30.
//  Copyright © 2017 Akin Shonibare. All rights reserved.
//

#pragma once
#include "stdafx.h"
// TODO: Backend Integration gives a "cannot open source file error"
#include "..\scugog_project\src\player.h"
#include "..\scugog_project\src\card.h"
#include "..\scugog_project\src\deck.h"
#include "..\scugog_project\src\environment.h"
#include "..\scugog_project\src\graveyard.h"

class Game
{
    
public:
    static void Start();
    
private:
    static bool IsExiting();
    static void GameLoop();
	//static void PlayGame(Player,Player);
    
    static void ShowSplashScreen();
    static void ShowMenu();
    //static void ChooseDeck();
    static void ShowInstructions();
    static int ShowCD1();
    static int ShowCD2();
	// TODO: Backend Integration gives a "cannot open source file error"
	static void ActivateGame(Environment env);
    
    
    
    enum GameState { Uninitialized, ShowingSplash, Paused,
        ShowingMenu, ShowingInstructions, Playing, Exiting, ShowingCD1, ShowingCD2};
    
    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
   
};
