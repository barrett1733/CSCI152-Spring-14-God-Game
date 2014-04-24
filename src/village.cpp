﻿#include <iostream>

#include "village.h"

typedef MobileEntityReference VillagerReference;

Village::Village(Faction faction) :
faction(faction), villageStarted(false), setBeginningPopCap(false)
{ }

void Village::importEntity(EntityReference entity)
{
	Faction faction = entity->getFaction();
	EntityGroup group = entity->getGroup();
	if(faction == this->faction)
	{
		switch(group)
		{
		case EG_VILLAGER:
			villagerList.push_back((MobileEntityReference)entity);
			break;

		case EG_DOMESTIC:
			domesticList.push_back((MobileEntityReference)entity);
			break;

		case EG_BUILDING:
			buildingList.push_back(entity);
			break;

		default: break;
		}
	}
}

void Village::update()
{
	// decideAction();

	//if (!setBeginningPopCap)
	//	setPopulationCap();

	// TODO: Village::runVillageLogic();
	// Check size of job queue vs population
	// Check next script instruction
	// Issue jobs
	// jobManager.issueJob(...);
}
	// TODO: Clean out dead entities.
void Village::villageStart()
{
	// meant for the beginning of the game
	villageStarted = true;
	buildHouse();
	buildHouse();
	buildHouse();
}
void Village::decideAction()
{
	if (!villageStarted)
		villageStart();
	if (villagerList.size() % 6 == 0)
		buildFoundary();
	if (villagerList.size() == populationCap)
		buildHouse();
	if (getBuildingCount(ET_HOUSE) % 8 == 0)
		buildMasonry();
	if (getBuildingCount(ET_HOUSE) % 6 == 0)
		buildMill();
	if (villagerList.size() % 15 == 0)
		buildSmith();
	if (villagerList.size() % 25 == 0)
		buildArmory();

}
int Village::getBuildingCount(EntityType entityType)
{
	int count = 0;
	for (int i = 0; i < buildingList.size(); i++)
		if (buildingList.at(i)->getEntityType() == entityType)
			count++;
	return count;
}

Position Village::getTownCenter()
{
    //Get TownCenter position
    Position p;
    
    for (EntityIter iter = buildingList.begin(); iter != buildingList.end(); ++iter)
    {
        if ((*iter)->getEntityType() == ET_TOWN_CENTER)
        {
            p = (*iter)->getPosition();
        }
    }
    
    //Find the nearest unoccupied area
    return p;
}

//Use BFS to find the nearest available area from a given position
Position Village::getAvaiableArea(Position p)
{
    WorldGeneration world(0);
    std::queue<Position> que;
    Position current, temp;
    if (world.world_positions[p.getY()][p.getX()] == ET_NONE)
        return p;
    else
    {
        que.push(p);
        while(!que.empty())
        {
            current = que.front();
            temp = current;
            que.pop();
            temp.move(D_UP);
            if (world.world_positions[temp.getY()][temp.getX()] == ET_NONE)
                current = temp;
            else
            {
                que.push(temp);
                temp = current;
                temp.move(D_DOWN);
                if (world.world_positions[temp.getY()][temp.getX()] == ET_NONE)
                    current = temp;
                else
                {
                    que.push(temp);
                    temp = current;
                    temp.move(D_LEFT);
                    if (world.world_positions[temp.getY()][temp.getX()] == ET_NONE)
                        current = temp;
                    else
                    {
                        que.push(temp);
                        temp = current;
                        temp.move(D_LEFT);
                        if (world.world_positions[temp.getY()][temp.getX()] == ET_NONE)
                            current = temp;
                    }
                    
                }
                
            }
        }
    }
    return current;
}

void Village::setPopulationCap()
{
	setBeginningPopCap = true;
	populationCap = villagerList.size();
}
void Village::buildHouse()
{
	populationCap += 3;
	std::cout << "Village::buildHouse()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(JOB_BUILD_HOUSE);
	// if(resourceManager.reserve(ResourceCost))
    //  target = getAvailableArea();
	// 	jobManager.createJob(JOB_BUILD_HOUSE, priority, target);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, priority, ResourceCost);
}
void Village::buildMasonry()
{
	std::cout << "Village::buildMasonry()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(JOB_BUILD_MASONRY);
	// if(resourceManager.reserve(ResourceCost))
	// 	jobManager.createJob(JOB_BUILD_MASONRY);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, ResourceCost);
}
void Village::buildMill()
{
	std::cout << "Village::buildMill()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(JOB_BUILD_MILL);
	// if(resourceManager.reserve(ResourceCost))
	// 	jobManager.createJob(JOB_BUILD_MILL);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, ResourceCost);
}
void Village::buildSmith()
{
	std::cout << "Village::buildSmith()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(JOB_BUILD_SMITH);
	// if(resourceManager.reserve(ResourceCost))
	// 	jobManager.createJob(JOB_BUILD_SMITH);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, ResourceCost);
}
void Village::buildArmory()
{
	std::cout << "Village::buildArmory()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(JOB_BUILD_ARMORY);
	// if(resourceManager.reserve(ResourceCost))
	// 	jobManager.createJob(JOB_BUILD_ARMORY);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, ResourceCost);
}
void Village::buildFoundary()
{
	std::cout << "Village::buildFoundary()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(JOB_BUILD_FOUNDARY);
	// if(resourceManager.reserve(ResourceCost))
	// 	jobManager.createJob(JOB_BUILD_FOUNDARY);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, ResourceCost);
}
