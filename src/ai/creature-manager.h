#pragma once
#include <vector>
#include "../entity-mobile.h"

class CreatureManager
{
	std::vector<MobileEntityReference> creatureList; // list of creatures

public:
	CreatureManager();
	~CreatureManager();
	void importEntity(EntityReference);
	MobileEntityReference getACreature();
	void update();
};

