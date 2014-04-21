#include "entity.h"
#include "job-manager.h"
#include <vector>

#pragma once

class Creature
{
	Faction faction;

	std::vector<MobileEntityReference> domesticList; // list of domestic things (cow)
	std::vector<MobileEntityReference> passiveList; // list of passive things (deer)
	std::vector<MobileEntityReference> hostileList; // list of hostile things (orges, wolves)

public:
	Creature(Faction);

	void importEntity(EntityReference);

	void wander();
	void attack();
	void flee();

	void update();

	Faction getFaction() { return faction; }
};

typedef Creature * CreatureReference;
