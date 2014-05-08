#include <iostream>

#include "village.h"

typedef MobileEntityReference VillagerReference;

Village::Village(Faction faction) :
	townCenter(0),
	faction(faction), 
	villageStarted(false)
{
	load("res/village.cfg");
}

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
	// might be entity type problem detection
	// which will cause job spam
	// -SB
	// decideAction();
}
void Village::villageStart()
{
	// meant for the beginning of the game
	villageStarted = true;
	for (int i = 0; i < amountOfStartingHouses; i++)
		build(JOB_BUILD_HOUSE);
}
void Village::decideAction()
{
	if (!villageStarted)
		villageStart();
	if (villagerList.size() > 0)
	{
		if (villagerList.size() / getBuildingCount(ET_FOUNDARY) > buildingRatios[BR_FOUNDARY])
			build(JOB_BUILD_FARM);
		if (villagerList.size() / getBuildingCount(ET_HOUSE) > buildingRatios[BR_HOUSE])
			build(JOB_BUILD_HOUSE);
		if (villagerList.size() / getBuildingCount(ET_MASONRY) > buildingRatios[BR_MASONRY])
			build(JOB_BUILD_STONEWORKS);
		if (villagerList.size() / getBuildingCount(ET_MILL) > buildingRatios[BR_MILL])
			build(JOB_BUILD_LUMBERMILL);
		if (villagerList.size() / getBuildingCount(ET_SMITH) > buildingRatios[BR_SMITH])
			build(JOB_BUILD_WEAPONSMITH);
		if (villagerList.size() / getBuildingCount(ET_ARMORY) > buildingRatios[BR_ARMORY])
			build(JOB_BUILD_ARMORSMITH);
	}
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

void Village::build(JobType job)
{
	std::cout << "Village::build()" << std::endl;
	// ResourceCost = jobManager.getResourceCost(job);
	// if(resourceManager.reserve(ResourceCost))
    //  target = getAvailableArea();
	// 	jobManager.createJob(job, priority, target);
	// else
	// 	jobManager.createJob(GATHER_RESOURCE, priority, ResourceCost);
}

bool Village::setProperty(std::string property, double value)
{
	if (property == "starting_houses")
	{
		amountOfStartingHouses = value;
		return true;
	}
	else if (property == "house_ratio")
	{
		buildingRatios[BR_HOUSE] = value;
	}
	else if (property == "mill_ratio")
	{
		buildingRatios[BR_MILL] = value;
	}
	else if (property == "masonry_ratio")
	{
		buildingRatios[BR_MASONRY] = value;
	}
	else if (property == "foundary_ratio")
	{
		buildingRatios[BR_FOUNDARY] = value;
	}
	else if (property == "smith_ratio")
	{
		buildingRatios[BR_SMITH] = value;
	}
	else if (property == "armory_ratio")
	{
		buildingRatios[BR_ARMORY] = value;
	}
}