
#include <iostream>
#include <sstream>
#include "game-manager.h"
#include "sdl-triangle-slider.h"
#include "villager-ai.h"

inline std::string toString(double x)
{
  std::ostringstream o;
  o << x;
  return o.str();
}

int main(int argc, char **argv)
{
	VillagerAI test(1,1);
	ResourceManager rtest;
	rtest.sendResource(RS_FOOD, 100);
	std::cout<<"RM Food: "<<rtest.getResourceAmount(RS_FOOD)<<std::endl;
	test.switchResourcePool(rtest);
	std::cout<<"VillAI Access Food:"<<test.getResourceAmount(RS_FOOD)<<std::endl;

	GameManager game;

	return 0;
}
