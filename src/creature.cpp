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
void Creature::wander(MobileEntityReference mobileEntity)
{
	Position pos = mobileEntity->getPosition();
	std::vector<Direction> openDirections = checkArea(mobileEntity->getPosition());
	pos.move(openDirections.at(rand() % openDirections.size()));
	mobileEntity->setPosition(pos);
}
void Creature::attack()
{

}

void Creature::flee()
{

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
