#include "resource-manager.h"
#include "job-manager.h"

#ifndef VILLAGE_H_
#define VILLAGE_H_

class Village
{
	Faction faction;
	ResourceManager resourceManager;
	JobManager jobManager;

	void balanceJobs();
	void createBuildings();
	void needsDefending();

public:
	Village(Faction);
	void run();

	bool hasGodLogic();
	void runGodLogic();
	void runVillageLogic();

	Faction getFaction() { return faction; }
};

typedef Village * VillageReference;

#endif
