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
#include "movement/pathfinding.h"

int main(int argc, char **argv)
{
	bool debug = false;
	if (debug)
	{
		//std::cin.ignore();
		Pathfinding test;

		if (false)
		{
			ObstructionMap testmap1(150);
			testmap1.set(Position(3, 0), OT_OBSTRUCTED);
			testmap1.set(Position(3, 1), OT_OBSTRUCTED);
			testmap1.set(Position(3, 2), OT_OBSTRUCTED);
			testmap1.set(Position(3, 3), OT_OBSTRUCTED);
			std::cout << "Test 1" << std::endl;
			test.findPath(Position(0, 0), Position(140, 0), &testmap1);
		}

		ObstructionMap testmap2(150);
		testmap2.set(Position(2, 1), OT_OBSTRUCTED);
		testmap2.set(Position(3, 1), OT_OBSTRUCTED);
		testmap2.set(Position(3, 2), OT_OBSTRUCTED);
		testmap2.set(Position(2, 3), OT_OBSTRUCTED);
		testmap2.set(Position(3, 3), OT_OBSTRUCTED);
		std::cout << "Test 2" << std::endl;
		test.findPath(Position(0, 2), Position(4, 2), &testmap2);

		ObstructionMap testmap3(150);
		testmap3.set(Position(2, 0), OT_OBSTRUCTED);
		testmap3.set(Position(2, 1), OT_OBSTRUCTED);
		testmap3.set(Position(2, 2), OT_OBSTRUCTED);
		testmap3.set(Position(1, 2), OT_OBSTRUCTED);
		testmap3.set(Position(0, 2), OT_OBSTRUCTED);
		std::cout << "Test 3" << std::endl;
		test.findPath(Position(0, 0), Position(4, 2), &testmap3);

		ObstructionMap testmap4(150);
		std::cout << "Test 4" << std::endl;
		test.findPath(Position(0, 0), Position(4, 2), &testmap4);

		std::cin.ignore();
	}
	if (!debug)
	{
		GameStateManager game;
		GameMode gameMode = GM_ERROR;

		GameManager gameManager;


		std::cout << "Starting Game Loop" << std::endl;
		sdl.launchWindow("Window Title!", 800, 600);
		while (game.mode() == GM_MENU)
			sdl.update();

		if (game.mode() == GM_PLAYING)
		{
			std::cout << "Setting up new game." << std::endl;
			// do world gen, set up new game, etc.

			gameManager.setup();

			std::cout << "Setting up new game completed." << std::endl;
		}

		std::cout << "Continuing Game Loop" << std::endl;
		long timer = 0;
		while ((gameMode = game.mode()) != GM_QUITTING)
		{
			if (gameMode == GM_PLAYING)
			{
				if (timer < time(0))
				{
					timer = time(0);
					//gameManager.sightCheck();
					gameManager.update();
				}

			}

			else if (gameMode == GM_PAUSING)
			{
				gameManager.hide();
			}

			sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
		}
	}
	return 0;
}
