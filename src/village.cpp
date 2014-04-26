#include <iostream>

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

Position Village::getTownCenter()
{
	// How often is this going to be called?
	// Is it better to just store the as a property of the village?
	// -CH

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
	populationCap += 3; //  MAGIC: why three? Config file, imo. -CH
	std::cout << "Village::buildHouse()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(JOB_BUILD_HOUSE);
	// if(resourceManager.reserve(ResourceCost))
    //  target = getAvailableArea();
	// 	jobManager.createJob(JOB_BUILD_HOUSE, priority, target);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, priority, ResourceCost);
}

//  The following functions are are nearly identical and should be abstracted.
//  void Village::buildSomething(EntityType buildingType);
// -CH
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
