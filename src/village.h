#include "creature.h"
#include "resource-manager.h"
#pragma once
class Village : public Creature
{
private:
	ResourceManager resourceManager;
	void balanceJobs();
	void createBuildings();
	void needsDefending();

public:
	Village();
	~Village();
	void run();
};

