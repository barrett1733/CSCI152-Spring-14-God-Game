
#include <iostream>
#include <sstream>
#include "game-manager.h"
#include "villager-ai.h"


int main(int argc, char **argv)
{
	GameManager game;

	// While application is running
	std::cout << "Starting Game Loop" << std::endl;
	while(game.mode() != GM_QUITING)
	{
		sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
	}

	return 0;
}
