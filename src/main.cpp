//
//  File: main.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Main function
//

#include <iostream>
#include <sstream>
#include <ctime>
#include "game-state-manager.h"
#include "game-manager.h"
#include "world-gen.h"

int main(int argc, char **argv)
{
	GameStateManager game;
	GameMode gameMode = GM_ERROR;

	GameManager gameManager;

	std::cout << "Starting Game Loop" << std::endl;
	sdl.launchWindow("Window Title!", 800, 600);
	while(game.mode() == GM_MENU)
		sdl.update();

	if(game.mode() == GM_PLAYING)
	{
		std::cout << "Setting up new game." << std::endl;
		// do world gen, set up new game, etc.

		gameManager.setup();

		std::cout << "Setting up new game completed." << std::endl;
	}

	std::cout << "Continuing Game Loop" << std::endl;
	long timer = 0;
	while(( gameMode = game.mode() ) != GM_QUITTING)
	{
		if(gameMode == GM_PLAYING)
		{
			if(timer < time(0))
			{
				timer = time(0);
				//gameManager.sightCheck();
				gameManager.update();
			}

		}

		else if(gameMode == GM_PAUSING)
		{
			gameManager.hide();
		}

		sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
	}
	return 0;
}
