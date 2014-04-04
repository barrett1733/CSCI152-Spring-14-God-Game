
#include <iostream>
#include <sstream>
#include "game-manager.h"
#include "entity-manager.h"
#include "player-manager.h"
#include "world-gen.h"
#include "time.h"

int main(int argc, char **argv)
{
	GameManager game;
	PlayerManager playerManager(EASY);
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
		playerManager.addCreaturePlayer();
		playerManager.addHumanPlayer(FT_PLAYER_1);
		playerManager.addHumanPlayer(FT_PLAYER_2);

		Entity entity = world.getNextEntity();
		while(entity.getType() != ET_NONE)
		{
			entityManager.createEntity(&entity);
			entity = world.getNextEntity();
		}
	}

	std::cout << "Continuing Game Loop" << std::endl;
	long timer = time(0);
	while(( gameMode = game.mode() ) != GM_QUITTING)
	{
		if(gameMode == GM_PLAYING)
		{
			if(timer < time(0))
			{
				timer = time(0);
				playerManager.update();
			}

			entityManager.update();
		}

		else if(gameMode == GM_PAUSING)
			entityManager.hide();

		sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
	}
	return 0;
}
