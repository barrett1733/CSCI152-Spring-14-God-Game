
#ifndef VILLAGE_MANAGER_H_
#define VILLAGE_MANAGER_H_

#include <vector>
#include <map>

#include "village.h"
#include "entity.h"

class VillageManager
{
	std::vector<VillageReference> villageList;
	std::vector<EntityReference> resourceList;

	std::map<Faction, VillageReference> villageMap;

	bool visible;

public:
	VillageManager();

	long addVillage(Faction);
	VillageReference getVillage(Faction);

	void importEntity(EntityReference);

	void show();
	void hide();
	void update();

	EntityReference getTownCenter(Faction);
};

#endif
