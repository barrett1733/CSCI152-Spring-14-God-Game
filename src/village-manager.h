
#ifndef VILLAGE_MANAGER_H_
#define VILLAGE_MANAGER_H_

#include <vector>
#include "village.h"

class VillageManager
{
	std::vector<VillageReference> villageList;

public:
	VillageManager();

	int addVillage(Faction);

	void update();
};

#endif
