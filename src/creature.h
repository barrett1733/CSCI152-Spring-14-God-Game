#pragma once
#include "entity.h"
#include "random-pathfinding.h"
#include <vector>

class Creature : public RandomPathfinding
{
	std::vector<MobileEntityReference> creatureList; // list of creatures

public:
	Creature();
	void importEntity(EntityReference);
	void decideAction(MobileEntityReference);
	void wander(MobileEntityReference);
	void attack();
	void flee();
	MobileEntityReference getACreature();
	void update();
};

typedef Creature * CreatureReference;
