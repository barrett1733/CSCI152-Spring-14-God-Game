#include "resource-manager.h"

#ifndef VILLAGER_AI_H_
#define VILLAGER_AI_H_

class VillagerAI : public ResourceManager
{
private:
	int optionalOption;
	void balanceJobs();
	void createBuildings();
	void needsDefending();
public:
	void run();
};

#endif