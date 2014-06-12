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

	GameManager entityManager;
	entityManager.setWorldSize(worldSize);

	std::cout << "Starting Game Loop" << std::endl;
	sdl.launchWindow("Window Title!", 800, 600);
	while(game.mode() == GM_MENU)
		sdl.update();

	if(game.mode() == GM_PLAYING)
	{
		std::cout << "Setting up new game." << std::endl;
		// do world gen, set up new game, etc.

		entityManager.setup();
	}

	std::cout << "Continuing Game Loop" << std::endl;
	long timer = time(0) + 1;
	while(( gameMode = game.mode() ) != GM_QUITTING)
	{
		if(gameMode == GM_PLAYING)
		{
			if(timer < time(0))
			{
				timer = time(0);
				//entityManager.sightCheck();
				entityManager.update();
			}

		}

		else if(gameMode == GM_PAUSING)
		{
			entityManager.hide();
		}

		sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
	}
	return 0;
}
