#include "computer-ai.h"


ComputerAI::ComputerAI(int faction, AiDifficulty diff) : ActorAI(faction,diff)
{
	for(int i=0;i<JT_COUNT;i++)
		jobsArray[i];
}

ComputerAI::~ComputerAI(void)
{
}

void ComputerAI::run()
{

}
bool ComputerAI::requestVillager(JobType job, int amount)
{
	if(amount <= villagers)
	{
		jobsArray[job] += amount;
		int remainder = amount%2;
		for(int i=0;i<JT_COUNT-1;i++)
			if(i != job)
				jobsArray[i] += amount/2;
		jobsArray[JT_COUNT-2] += remainder;
		return true;
	}
	else return false;
}