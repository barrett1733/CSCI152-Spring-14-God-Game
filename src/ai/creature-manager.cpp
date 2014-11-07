#include "creature-manager.h"

CreatureManager::CreatureManager()
{
	creatureList.reserve(200);
}

void CreatureManager::import(Entity* entity)
{
	// issue with import
	EntityGroup group = entity->getGroup();
	if (group == EG_DOMESTIC || group == EG_HOSTILE || group == EG_PASSIVE)
		creatureList.push_back((MobileEntityReference)entity);
}

void CreatureManager::decideAction()
{
	// cows always wander
	// deer wander until see another mobileEntity that is not deer
	// wolves wander until see another target that is not wolf or orge
	// orges do the same as wolves
	for (int i = 0; i < creatureList.size(); i++)
	{
		EntityGroup creatureGroup = creatureList[i]->getGroup();
		if (creatureGroup == EG_DOMESTIC)
			wander(creatureList[i]);
		if (creatureGroup == EG_PASSIVE)
			wander(creatureList[i]);
		if (creatureGroup == EG_HOSTILE)
			wander(creatureList[i]);
	}
}

void CreatureManager::wander(MobileEntity* mobileEntity)
{
	Position pos = mobileEntity->getPosition();
	int randnum = (rand() % (D_COUNT - D_NORTH)) + D_NORTH;
	pos.move(randnum);
}

void CreatureManager::attack(MobileEntity* mobileEntity)
{
	// Detect entities in range
	// Wolves and orges attack everything not hostile
	// -SB
}

void CreatureManager::flee(MobileEntity* mobileEntity)
{
	// If Villager, Wolf, Orge in range flee opposite direction
	// Deer

}

void CreatureManager::update(ObstructionMap* obstructionMap)
{
	decideAction();
}
