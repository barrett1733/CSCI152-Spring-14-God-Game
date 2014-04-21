
#ifndef VILLAGE_MANAGER_H_
#define VILLAGE_MANAGER_H_

#include <vector>
#include "village.h"
#include "entity-manager.h"

class VillageManager
{
	std::vector<VillageReference> villageList;

	std::vector<EntityReference> resourceList;

public:
	VillageManager();

	long addVillage(Faction);

	void importEntity(EntityReference);

	void update();
};

#endif
