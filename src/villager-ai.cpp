#include "villager-ai.h"


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
		total += getResourceAmount(ResourceType(i));
	average = total/RT_COUNT;

	for(int i = 0; i < RT_COUNT; i++)
		if(getResourceAmount(ResourceType(i)) < average)
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