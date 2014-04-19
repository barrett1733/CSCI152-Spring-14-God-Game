
#include "village-manager.h"

VillageManager::VillageManager()
{

}

long VillageManager::addVillage(Faction faction)
{
	villageList.push_back(new Village(faction));
	return villageList.size();
}

void VillageManager::importEntity(EntityReference entity)
{
	long villageCount = villageList.size();
	for(long villageIndex = 0; villageIndex < villageCount; villageIndex ++)
		villageList[villageIndex]->importEntity(entity);

	if(entity->getGroup() == EG_RESOURCE || entity->getFaction() == FT_STATIC)
		resourceList.push_back(entity);
}

void VillageManager::update()
{
	// TODO: Clean out dead entities from resource list.

	long villageCount = villageList.size();
	for(long villageIndex = 0; villageIndex < villageCount; villageIndex ++)
	{
		VillageReference village = villageList[villageIndex];

		if( village->hasGodLogic() )
			village->runGodLogic();

		village->update();
	}
}
