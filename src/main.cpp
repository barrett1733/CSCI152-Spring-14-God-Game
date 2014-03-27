
#include <iostream>
#include <sstream>
#include "game-manager.h"
#include "entity-manager.h"
#include "world_gen.h"

int main(int argc, char **argv)
{
	GameManager game;
	GameMode gameMode = GM_ERROR;

	// While application is running
	std::cout << "Starting Game Loop" << std::endl;
	while(( gameMode = game.mode() ) != GM_QUITTING)
	{
		sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
	}

	return 0;
}
