#include "village.h"

typedef MobileEntityReference VillagerReference;

Village::Village(Faction faction) :
	faction(faction)
{ }

void Village::importEntity(EntityReference entity)
{
	Faction faction = entity->getFaction();
	EntityGroup group = entity->getGroup();
	if(faction == this->faction)
	{
		if(group == EG_VILLAGER)
			villagerList.push_back((MobileEntityReference)entity);

		else if(group == EG_DOMESTIC)
			domesticList.push_back((MobileEntityReference)entity);
	}
}

bool Village::hasGodLogic()
{
	return false;
}

void Village::runGodLogic()
{
	// TODO: Village::runGodLogic();
	// Determine military action
	// Determine miracles
	// Determine Triangle balance.
	// jobManager.setBalance(militaryBalance, buildBalance, gatherBalance);
}

void Village::update()
{
	// TODO: Village::runVillageLogic();
	// Check size of job queue vs population
	// Check next script instruction
	// Issue jobs
	// jobManager.issueJob(...);

	// TODO: Clean out dead entities.
void Village::buildHouse()
{
	std::cout << "Village::buildHouse()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(JOB_BUILD_HOUSE);
	// if(resourceManager.reserve(ResourceCost))
	// 	jobManager.createJob(JOB_BUILD_HOUSE);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, ResourceCost);
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
