#pragma once
#include "entity.h"
#include "pathfinding.h"
#include <vector>

class Creature : public Pathfinder
{
	std::vector<MobileEntityReference> domesticList; // list of domestic things (cow)
	std::vector<MobileEntityReference> passiveList; // list of passive things (deer)
	std::vector<MobileEntityReference> hostileList; // list of hostile things (orges, wolves)

public:
	Creature();
	void importEntity(EntityReference);

	void wander(MobileEntityReference);
	void attack();
	void flee();
	MobileEntityReference getACreature();
	void update();
};

typedef Creature * CreatureReference;
