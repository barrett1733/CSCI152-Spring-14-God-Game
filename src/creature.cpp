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
	for (int i = 0; i < domesticList.size(); i++)
		wander(domesticList.at(i));
	for (int i = 0; i < passiveList.size(); i++)
		wander(passiveList.at(i));
	for (int i = 0; i < hostileList.size(); i++)
		wander(hostileList.at(i));
}
