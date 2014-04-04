#include "player-human.h"

PlayerHuman::PlayerHuman(Faction faction) :
	Player(faction)
{ }

bool PlayerHuman::hasGodLogic()
{
	return false;
}

void PlayerHuman::runGodLogic()
{
	// TODO: Village::runGodLogic();
	// Determine military action
	// Determine miracles
	// Determine Triangle balance.
	// jobManager.setBalance(militaryBalance, buildBalance, gatherBalance);
}

void Village::runVillageLogic()
{
	// TODO: Village::runVillageLogic();
	// Check size of job queue vs population
	// Check next script instruction
	// Issue jobs
	// jobManager.issueJob(...);
}

void Village::run()
{
	balanceJobs();
	createBuildings();
	needsDefending();
}

void Village::balanceJobs()
{
	// int total = 0;
	// int average = 0;
	// for(int i = 0; i < RT_COUNT; i++)
	// 	total += getResourceAmount(ResourceType(i), faction);
	// average = total/RT_COUNT;

	// for(int i = 0; i < RT_COUNT; i++)
	// 	if(getResourceAmount(ResourceType(i), faction) < average)
	// 		;//createGatherJob(ResourceType(i));

	//gather
	//create
	//	check position of building to create - another class?
	//defend
	//	check position attacked - another class?
}

void Village::createBuildings()
{

}

void Village::needsDefending()
{

}
