
#include <vector>

#include "resource-manager.h"
#include "job-manager.h"

#ifndef VILLAGE_H_
#define VILLAGE_H_

class Village
{
	Faction faction;
	ResourceManager resourceManager;
	JobManager jobManager;

	std::vector<MobileEntityReference> villagerList; // list of employable villagers
	std::vector<MobileEntityReference> domesticList; // list of domestic things (cows)
	std::vector<EntityReference> buildingList; // list of buildings
	// Should resources be 'discovered' instead of all known immediately?
	//
	// TODO: Villager creation every 30 secs
	//
	bool villageStarted;
	int populationCap;
	bool setBeginningPopCap;

	void villageStart();

	void decideAction();

	int getBuildingCount(EntityType);
	void setPopulationCap();

	void buildHouse();
	void buildMasonry();
	void buildMill();
	void buildSmith();
	void buildArmory();
	void buildFoundary();

public:
	Village(Faction);

	void importEntity(EntityReference);

	void update();


	Faction getFaction() { return faction; }
};

typedef Village * VillageReference;

#endif
