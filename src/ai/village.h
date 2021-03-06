//
//  File: village.h
//  Author: Chad Hatcher, Steven Barrett, Jimmy Ouyang
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Village Class Definition
// Maintains a collection of faction-aligned Entities.
// Maintains a Job Manager and Resource Manager.
//

#include <vector>

#include "../job/resource-manager.h"
#include "../job/job-manager.h"
#include "../world-gen.h"
#include "../movement/Movement.h"

#ifndef VILLAGE_H_
#define VILLAGE_H_

class Village
{
	EntityReference townCenter;
	Faction faction;
	ResourceManager resourceManager;
	JobManager jobManager;

	std::vector<MobileEntityReference> villagerList; // list of employable villagers
	std::vector<MobileEntityReference> domesticList; // list of domestic things (cows)
	std::vector<EntityReference> buildingList; // list of buildings

	// Should resources be 'discovered' instead of all known immediately?
	//
	// TODO: Villager creation every 30 secs
	// NOTE: ^ driven from the outside. A Village probably doesn't need to maintain a concept of 'time'. -CH
	// + bool hasFoodToSpawnVillager();
	// + void spawnVillager();
	//
	bool villageStarted;
	int populationCap;
	bool setBeginningPopCap;

	int availableHousing;

	void villageStart();

	void decideAction(ObstructionMapReference);

	int getBuildingCount(EntityType);
	void setPopulationCap();

    Position getAvaiableArea(Position);

public:
	Village(Faction);

	void import(EntityReference);

	void update(ObstructionMapReference);

	EntityReference getTownCenter();

	void build(JobType, ObstructionMapReference);

	Faction getFaction() { return faction; }
};

typedef Village * VillageReference;
typedef std::vector<EntityReference> EntityList;
typedef EntityList::iterator EntityIter;


#endif
