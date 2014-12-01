#pragma once
#include <vector>
#include "../entity.h"

class CreatureManager
{
	std::vector<MobileEntity*> creatureList; // list of creatures
	std::vector<MobileEntity*> villagerList; // list of creatures
	ObstructionMap* obstructionMap;
	int evaluateFleeDirection(MobileEntity* creature, MobileEntity* enemy, Direction);
	bool inRange(Position origin, Position enemy, double sightrange);

public:
	CreatureManager();
	void import(Entity*);
	void decideAction();
	void wander(MobileEntity*);
	void attack(MobileEntity*);
	Direction flee(MobileEntity*);
	void update(ObstructionMap*);
};

