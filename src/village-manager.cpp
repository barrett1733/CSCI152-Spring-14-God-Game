
#include <iostream>

#include "village-manager.h"

VillageManager::VillageManager()
{
	hide();
}

long VillageManager::addVillage(Faction faction)
{
	VillageReference village = new Village(faction);

	villageMap[faction] = village;
	villageList.push_back(village);

	return villageList.size();
}

void VillageManager::importEntity(EntityReference entity)
{
	long villageCount = villageList.size();
	for(long villageIndex = 0; villageIndex < villageCount; villageIndex ++)
		villageList[villageIndex]->importEntity(entity);

	if(entity->getGroup() == EG_RESOURCE || entity->getFaction() == F_STATIC)
		resourceList.push_back(entity);
}

void VillageManager::show()
{
	if(visible) return;
	visible = true;
}

void VillageManager::hide()
{
	if(!visible) return;
	visible = false;
}

void VillageManager::update()
{
	show();
	// TODO: Clean out dead entities from resource list.

	long villageCount = villageList.size();
	for(long villageIndex = 0; villageIndex < villageCount; villageIndex ++)
	{
		VillageReference village = villageList[villageIndex];
		village->update();
	}
}

EntityReference VillageManager::getTownCenter(Faction faction)
{
	VillageReference village = villageMap[faction];
	return village->getTownCenter();
}

void VillageManager::buildHouse()
{
	std::cout << "VillageManager::buildHouse()" << std::endl;
	villageList[0]->buildHouse();
}
