//
//  File: village.cpp
//  Author: Chad Hatcher, Steven Barrett, Jimmy Ouyang
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Village Class Implementation
//

#include <iostream>

#include "village.h"
#include "pathfinding.h"

const int POP_PER_HOUSE = 5;

typedef MobileEntityReference VillagerReference;

Village::Village(Faction faction) :
	townCenter(0),
	faction(faction),
	villageStarted(false),
	setBeginningPopCap(false),
	availableHousing(0)
{ }

void Village::import(EntityReference entity)
{
	Faction faction = entity->getFaction();
	EntityGroup group = entity->getGroup();
	EntityType type = entity->getEntityType();

	if(faction == this->faction)
	{
		switch(group)
		{
		case EG_VILLAGER:
			villagerList.push_back((MobileEntityReference)entity);

			availableHousing --;
			break;

		case EG_DOMESTIC:
			domesticList.push_back((MobileEntityReference)entity);
			break;

		case EG_BUILDING:
			buildingList.push_back(entity);

			switch(type)
			{
				case ET_TOWN_CENTER:
					if(townCenter)
						std::cerr << "A second town center? How fancy!" << std::endl;
					townCenter = entity;
				break;

				case ET_HOUSE:
					availableHousing += POP_PER_HOUSE;
					break;

				case ET_TEMPLE:
					break;

				default:
					break;
			}
			break;

		default: break;
		}
	}
}

void Village::update(ObstructionMapReference obstructionMap)
{
	// Testing pathfinding on villagers
	Pathfinding test;
	PositionList* toMove;
	int i = 0;
	Position goal = obstructionMap->findOpenPosition(Position(0, 0));
	/*
	toMove = test.findPath(goal, villagerList.at(0)->getPosition(), obstructionMap);
	if (!toMove->empty())
		villagerList.at(0)->setPosition(toMove->at(0));
		*/
	
	for (Entity* villager : villagerList)
	{
		toMove = &test.findPath(goal, villager->getPosition(), obstructionMap);
		if (!toMove->empty())
			villager->setPosition(toMove->at(0));
		std::cout << i << std::endl;
		i++;
	}

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
	//  MAGIC: Initial buildings should be from file, not hardcoded.
	// -CH
	// 3 house start
}

void Village::decideAction(ObstructionMapReference obstructionMap)
{

}
int Village::getBuildingCount(EntityType entityType)
{
	int count = 0;
	for (int i = 0; i < buildingList.size(); i++)
		if (buildingList.at(i)->getEntityType() == entityType)
			count++;
	return count;
}

EntityReference Village::getTownCenter()
{
	return townCenter;
}

//Use BFS to find the nearest available area from a given position
Position Village::getAvaiableArea(Position p)
{
	//
	// 1) Don't regenerate the whole world again
	// (it's theoretically expensive).
	// We got away with this previously because the seed was always zero;
	// but I just corrected it to time(0).
	//
	// 2) If Village needs access to the whole world,
	// then this logic is probably (but not necessarily) at the wrong level
	// (i.e. it should be higher up the chain).
	//
	// 3) This will only work *BEFORE THE FIRST TICK*, because after that,
	// entities will have moved, and there may be new entities.
	//
	// -CH
	//

	WorldGeneration world(0);
    std::queue<Position> que;
    Position current, temp;
    if (world.world_positions[p.getY()][p.getX()] != ET_NONE)
    {
        que.push(p);
        //  TODO: Refactor.
        // Nested if-statements like this is silly.
        // -CH
        while(!que.empty())
        {
            current = que.front();
            temp = current;
            que.pop();


            temp.move(D_UP);
            if (world.world_positions[temp.getY()][temp.getX()] == ET_NONE)
                return temp;
            que.push(temp);

            temp = current;
            temp.move(D_DOWN);
            if (world.world_positions[temp.getY()][temp.getX()] == ET_NONE)
                return temp;
            que.push(temp);

            temp = current;
            temp.move(D_LEFT);
            if (world.world_positions[temp.getY()][temp.getX()] == ET_NONE)
                return temp;
            que.push(temp);

            temp = current;
            temp.move(D_RIGHT);
            if (world.world_positions[temp.getY()][temp.getX()] == ET_NONE)
                return temp;
            que.push(temp);
        }
    }
    return p;
}

void Village::setPopulationCap()
{
	setBeginningPopCap = true;
	populationCap = villagerList.size();
}

void Village::build(JobType job, ObstructionMapReference obstructionMap)
{
	// House populationCap += 3; //  MAGIC: why three? Config file, imo. -CH
	std::cout << "Village::build(" << job << ")" << std::endl;
	// ResourceCost = jobManager.getResourceCost(job);
	// if(resourceManager.reserve(ResourceCost))
    //  target = getAvailableArea();
	// 	jobManager.createJob(job, priority, target);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, priority, ResourceCost);
}
