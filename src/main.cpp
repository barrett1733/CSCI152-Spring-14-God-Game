
#include <iostream>
#include <sstream>
#include "game-manager.h"
#include "entity-manager.h"
#include "village-manager.h"
#include "world-gen.h"

int main(int argc, char **argv)
{
	GameManager game;
	VillageManager villageManager;
	GameMode gameMode = GM_ERROR;

	WorldGeneration world(0);
	int worldSize = world.getWorldSize();

	EntityManager entityManager(worldSize);

	std::cout << "Starting Game Loop" << std::endl;
	sdl.launchWindow("Window Title!", 800, 600);
	while(game.mode() == GM_MENU)
		sdl.update();

	if(game.mode() == GM_PLAYING)
	{
		std::cout << "Setting up new game." << std::endl;
		// do world gen, set up new game, etc.

		villageManager.addVillage(FT_PLAYER_1);
		villageManager.addVillage(FT_PLAYER_2);

		Entity entity = world.getNextEntity();
		while(entity.getType() != ET_NONE)
		{
			entityManager.createEntity(&entity);
			entity = world.getNextEntity();
		}
	}

	std::cout << "Continuing Game Loop" << std::endl;
	int timer = time(0);
	while(( gameMode = game.mode() ) != GM_QUITTING)
	{
		if(gameMode == GM_PLAYING)
		{
			if(timer < time(0))
			{
				timer = time(0);
				villageManager.update();
			}

			entityManager.update();
		}

		else if(gameMode == GM_PAUSING)
			entityManager.hide();

		sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
	}
	return 0;
}
