#include "creature.h"

Creature::Creature()
{ }

void Creature::importEntity(EntityReference entity)
{
	EntityGroup group = entity->getGroup();
	if (group == EG_DOMESTIC)
		domesticList.push_back((MobileEntityReference)entity);
	else if (group == EG_PASSIVE)
		passiveList.push_back((MobileEntityReference)entity);
	else if (group == EG_HOSTILE)
		hostileList.push_back((MobileEntityReference)entity);
}

void Creature::attack()
{

}

void Creature::flee()
{

}

void Creature::wander(MobileEntityReference creature)
{
	int r = rand();
	switch (r % 4)
	{
	case 0:
		position.move(D_UP);
		break;

	case 1:
		position.move(D_RIGHT);
		break;

	case 2:
		position.move(D_DOWN);
		break;

	case 3:
		position.move(D_LEFT);
		break;
	}
}
void Creature::update()
{
	for (auto iter = domesticList.begin(); iter != domesticList.end(); ++iter)
		wander(*iter);
	for (auto iter = passiveList.begin(); iter != passiveList.end(); ++iter)
		wander(*iter);
	for (auto iter = hostileList.begin(); iter != hostileList.end(); ++iter)
		wander(*iter);
}
