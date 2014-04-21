#include "creature.h"

Creature::Creature(Faction faction) :
faction(faction)
{ }

void Creature::importEntity(EntityReference entity)
{
	Faction faction = entity->getFaction();
	EntityGroup group = entity->getGroup();
	if (faction == this->faction)
	{
		if (group == EG_DOMESTIC)
			domesticList.push_back((MobileEntityReference)entity);

		else if (group == EG_PASSIVE)
			passiveList.push_back((MobileEntityReference)entity);

		else if (group == EG_HOSTILE)
			hostileList.push_back((MobileEntityReference)entity);
	}
}

void Creature::attack()
{

}

void Creature::flee()
{

}

void Creature::wander(CreatureReference creature)
{
	
}
void Creature::update()
{
	for (std::iterator<Creature> *iter = passiveList.begin(); iter != passiveList.end(); ++iter)
		wander((MobileEntityReference) iter);
}
