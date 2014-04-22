
#include <iostream>
#include <sstream>
#include <ctime>
#include "game-manager.h"
#include "entity-manager.h"
#include "village-manager.h"
#include "world-gen.h"
#include "creature.h"

int main(int argc, char **argv)
{
	GameManager game;
	VillageManager villageManager;
	Creature creatures;
	GameMode gameMode = GM_ERROR;

	WorldGeneration world(0);
	int worldSize = world.getWorldSize();

	EntityManager entityManager(worldSize);

	std::cout << "Starting Game Loop" << std::endl;
	sdl.launchWindow("Window Title!", 800, 600);
	while(game.mode() == GM_MENU)
		sdl.update();

	EntityRecord * record;

	if(game.mode() == GM_PLAYING)
	{
		std::cout << "Setting up new game." << std::endl;
		// do world gen, set up new game, etc.

		villageManager.show();
		villageManager.addVillage(F_PLAYER_1);
		villageManager.addVillage(F_PLAYER_2);

		Entity entity = world.getNextEntity();
		while(entity.getType() != ET_NONE)
		{
			record = entityManager.createRecord(&entity);
			villageManager.importEntity(record->entity);
			//creatures.importEntity(record->entity);
			// Get next entity for next loop iteration.
			entity = world.getNextEntity();
		}

		entityManager.update();
		//creatures.world = &world;
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
				villageManager.update();
				//entityManager.sightCheck();
				//creatures.update();
				entityManager.update();
			}

		}

		else if(gameMode == GM_PAUSING)
		{
			villageManager.hide();
			entityManager.hide();
		}

		sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
	}
	return 0;
}
