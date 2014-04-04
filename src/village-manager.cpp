
#include "village-manager.h"

VillageManager::VillageManager()
{

}

long VillageManager::addVillage(Faction faction)
{
	villageList.push_back(new Village(faction));
	return villageList.size();
}

void VillageManager::update()
{
	long villageCount = villageList.size();
	for(long villageIndex = 0; villageIndex < villageCount; villageIndex ++)
	{
		VillageReference village = villageList[villageIndex];

		if( village->hasGodLogic() )
			village->runGodLogic();

		village->runVillageLogic();
	}
}
