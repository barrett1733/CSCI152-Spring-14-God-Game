#include "resource-manager.h"

#ifndef VILLAGER_AI_H_
#define VILLAGER_AI_H_

class VillagerAI : public ResourceManager
{
private:
	Faction myFaction;
	void balanceJobs();
	void createBuildings();
	void needsDefending();
public:
	VillagerAI(Faction);
	void run();
};

#endif
