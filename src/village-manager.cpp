//
//  File: village-manager.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Village Manager Implementation
//

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

VillageReference VillageManager::getVillage(Faction faction)
{
	return villageMap[faction];
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
	std::cerr << "\033[33m VillageManager::getTownCenter() is deprecated. \033[m" << std::endl;
	VillageReference village = villageMap[faction];
	return village->getTownCenter();
}
