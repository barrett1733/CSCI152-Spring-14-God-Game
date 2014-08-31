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

void VillageManager::addVillage(Faction faction)
{
	villageMap[faction] = new Village(faction);
}

VillageReference VillageManager::getVillage(Faction faction)
{
	return villageMap.at(faction);
}

void VillageManager::show()
{
	if (visible) return;
	visible = true;
}

void VillageManager::hide()
{
	if (!visible) return;
	visible = false;
}

void VillageManager::update(ObstructionMapReference obstructionMap)
{
	show();
	// TODO: Clean out dead entities from resource list.

	std::map<Faction, VillageReference>::iterator it;
	for (it = villageMap.begin(); it != villageMap.end(); ++it)
	{
			it->second->update(obstructionMap);
	}
}
