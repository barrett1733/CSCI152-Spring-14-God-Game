
#include <iostream>
#include <sstream>
#include "game-manager.h"
#include "villager-ai.h"


int main(int argc, char **argv)
{
	VillagerAI test(1,1);
	ResourceManager rtest;
	rtest.sendResource(RS_FOOD, 100);
	std::cout<<"RM Food: "<<rtest.getResourceAmount(RS_FOOD)<<std::endl;
	test.switchResourcePool(rtest);
	std::cout<<"VillAI Access Food:"<<test.getResourceAmount(RS_FOOD)<<std::endl;

	GameManager game;

	// While application is running
	std::cout << "Starting Game Loop" << std::endl;
	while(game.mode() != GM_QUITING)
	{
		sdl.update(); //  this should be the last call, because it will consume the rest of the frame's time.
	}

	return 0;
}
