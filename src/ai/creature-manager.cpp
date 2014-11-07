#include "creature-manager.h"

void CreatureManager::importEntity(EntityReference entity)
{
	EntityGroup group = entity->getGroup();
	if (group == EG_DOMESTIC || group == EG_HOSTILE || group == EG_PASSIVE)
		creatureList.push_back((MobileEntityReference)entity);
}

void CreatureManager::update()
{
	//for (int i = 0; i < creatureList.size(); i++)
	//	creatureList[i].decideAction();
}
