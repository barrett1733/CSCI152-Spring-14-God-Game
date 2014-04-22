#pragma once
#include "entity.h"
#include "job-manager.h"
#include <vector>

class Creature
{
private:
	std::vector<MobileEntityReference> domesticList; // list of domestic things (cow)
	std::vector<MobileEntityReference> passiveList; // list of passive things (deer)
	std::vector<MobileEntityReference> hostileList; // list of hostile things (orges, wolves)

public:
	Creature();

	void importEntity(EntityReference);

	void wander(MobileEntityReference);
	void attack();
	void flee();

	void update();
};

typedef Creature * CreatureReference;
