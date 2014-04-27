
#include <iostream>
#include <sstream>
#include <ctime>
#include "game-manager.h"
#include "entity-manager.h"
#include "world-gen.h"

int main(int argc, char **argv)
{
	GameManager game;
	GameMode gameMode = GM_ERROR;

	WorldGeneration world(0);
	int worldSize = world.getWorldSize();

	EntityManager entityManager(worldSize);
	JobManager::entityManager = &entityManager;

	std::cout << "Starting Game Loop" << std::endl;
	sdl.launchWindow("Window Title!", 800, 600);
	while(game.mode() == GM_MENU)
		sdl.update();

	if(game.mode() == GM_PLAYING)
	{
		std::cout << "Setting up new game." << std::endl;
		// do world gen, set up new game, etc.


		Entity entity = world.getNextEntity();
		while(entity.getType() != ET_NONE)
		{
			entityManager.createRecord(&entity);

			// Get next entity for next loop iteration.
			entity = world.getNextEntity();
		}

		entityManager.update();
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
