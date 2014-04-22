#pragma once
#include "entity.h"
#include "entity-manager.h"
#include "world-gen.h"
#include <vector>

class Creature
{
private:
	std::vector<MobileEntityReference> domesticList; // list of domestic things (cow)
	std::vector<MobileEntityReference> passiveList; // list of passive things (deer)
	std::vector<MobileEntityReference> hostileList; // list of hostile things (orges, wolves)

public:
	Creature();
	WorldGeneration * world;
	void importEntity(EntityReference);

	void wander(MobileEntityReference);
	void attack();
	void flee();

	std::vector<Direction> checkOpenAreas(Position);
	Direction checkDirection(int i, int j);
	void update();
};

typedef Creature * CreatureReference;
