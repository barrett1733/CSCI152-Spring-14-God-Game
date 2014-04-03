
#include "village-manager.h"

VillageManager::VillageManager()
{

}

int VillageManager::addVillage(Faction faction)
{
	villageList.push_back(new Village(faction));
	return villageList.size();
}

void VillageManager::update()
{
	int villageCount = villageList.size();
	for(int villageIndex = 0; villageIndex < villageCount; villageIndex ++)
	{
		VillageReference village = villageList[villageIndex];

		if( village->hasGodLogic() )
			village->runGodLogic();

		village->runVillageLogic();
	}
}
