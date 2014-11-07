#pragma once
#include <vector>
#include "../entity.h"

class CreatureManager
{
	std::vector<MobileEntity*> creatureList; // list of creatures

public:
	CreatureManager();
	void import(Entity*);
	void decideAction();
	void wander(MobileEntity*);
	void attack(MobileEntity*);
	void flee(MobileEntity*);
	void update(ObstructionMap*);
};

