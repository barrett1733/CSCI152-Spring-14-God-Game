#include "village-ai.h"

VillagerAI::VillagerAI(Faction faction):myFaction(faction)
{ }

void VillagerAI::run()
{
	balanceJobs();
	createBuildings();
	needsDefending();
}

void VillagerAI::balanceJobs()
{
	int total = 0;
	int average = 0;
	for(int i = 0; i < RT_COUNT; i++)
		total += getResourceAmount(ResourceType(i),myFaction);
	average = total/RT_COUNT;

	for(int i = 0; i < RT_COUNT; i++)
		if(getResourceAmount(ResourceType(i),myFaction) < average)
			;//createGatherJob(ResourceType(i));

	//gather
	//create
	//	check position of building to create - another class?
	//defend
	//	check position attacked - another class?
}

void VillagerAI::createBuildings()
{

}

void VillagerAI::needsDefending()
{

}
