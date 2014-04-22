
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

	void balanceJobs();
	void createBuildings();
	void needsDefending();

public:
	Village(Faction);
	void run();

	void importEntity(EntityReference);

	bool hasGodLogic();
	void runGodLogic();
	void update();

	void buildHouse();

	Faction getFaction() { return faction; }
};

typedef Village * VillageReference;

#endif
