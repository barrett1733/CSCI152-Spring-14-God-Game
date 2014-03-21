#include "player-ai.h";

PlayerAI::PlayerAI(int faction, AiDifficulty diff):faction(faction),myDifficulty(diff),delay(1),counter(0)
{
	myVillagerAI.registerResourcePool(myResourcePool);
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
		//makeDecisions();
	}
	counter++;
}
