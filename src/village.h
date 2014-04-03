#include "resource-manager.h"

#ifndef VILLAGE_H_
#define VILLAGE_H_

class Village : public ResourceManager
{
private:
	Faction myFaction;
	void balanceJobs();
	void createBuildings();
	void needsDefending();
public:
	Village(Faction);
	void run();
};

#endif
