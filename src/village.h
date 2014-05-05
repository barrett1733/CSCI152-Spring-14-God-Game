#ifndef VILLAGE_H_
#define VILLAGE_H_

#include <vector>

#include "resource-manager.h"
#include "job-manager.h"
#include "world-gen.h"
#include "config.h"

class Village : public Config
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
	bool villageStarted;
	int populationCap;

	bool hasFoodToSpawnVillager();
	void spawnVillager();

	void villageStart();

	void decideAction();

	int getBuildingCount(EntityType);

    Position getAvaiableArea(Position);
	bool setProperty(std::string property, int value);

public:
	Village(Faction);

	void importEntity(EntityReference);

	void update();

	EntityReference getTownCenter();

	void build(JobType);

	Faction getFaction() { return faction; }
};

typedef Village * VillageReference;
typedef std::vector<EntityReference> EntityVec;
typedef EntityVec::iterator EntityIter;


#endif
