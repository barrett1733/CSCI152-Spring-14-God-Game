#include <iostream>

#include "village.h"

typedef MobileEntityReference VillagerReference;

Village::Village(Faction faction) :
	townCenter(0),
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
			if(*entity == ET_TOWN_CENTER)
			{
				if(townCenter)
					std::cerr << "A second town center? How fancy!" << std::endl;
				townCenter = entity;
			}
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
	//  MAGIC: Initial buildings should be from file, not hardcoded.
	// -CH
	buildHouse();
	buildHouse();
	buildHouse();
}
void Village::decideAction()
{
	//  MAGIC: All these numbers should be loaded from a script file.
	// Also, to build a certain buildings at a certain population level is probably incorrect.
	// I.E.:
	// Population size reaches 12, so a foundary is built.
	// Someone dies, so population goes back to 11.
	// Then someone is born, so population goes back to 12,
	// so another foundary is built.
	// lololfoundarieseverywhere.
	// -CH
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
void Village::build(JobType job)
{
	// populationCap += 3; //  MAGIC: why three? Config file, imo. -CH
	std::cout << "Village::build()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(job);
	// if(resourceManager.reserve(ResourceCost))
    //  target = getAvailableArea();
	// 	jobManager.createJob(job, priority, target);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, priority, ResourceCost);
}
