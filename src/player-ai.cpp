#include "player-ai.h";
#include "villager-ai.h";
#include "resource-manager.h";


PlayerAI::PlayerAI(int faction, AiDifficulty diff):faction(faction),myDifficulty(diff),delay(1),counter(0)
{
	myVillagerAI.switchResourcePool(myResourceManager);
}

void makeDecisions()
{

}

void PlayerAI::run()
{
	if(counter >= delay)
	{
		counter = 0;
		myVillagerAI.run();
		makeDecisions();
	}
	counter++;
}
