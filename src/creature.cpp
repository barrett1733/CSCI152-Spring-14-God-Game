#include "creature.h"

Creature::Creature()
{ }

void Creature::importEntity(EntityReference entity)
{
	EntityGroup group = entity->getGroup();
	if (group == EG_DOMESTIC || group == EG_HOSTILE || group == EG_PASSIVE)
		creatureList.push_back((MobileEntityReference)entity);
}
void Creature::decideAction(MobileEntityReference mobileEntity)
{
	// how to handle mobileEntity sight range?
	// -SB

	if (mobileEntity->getGroup() == EG_DOMESTIC)
		wander(mobileEntity);
	// cows always wander
	// deer wander until see another mobileEntity that is not deer
	// wolves wander until see another target that is not wolf or orge
	// orges do the same as wolves
}
void Creature::wander(MobileEntityReference mobileEntity)
{
	// Entity wander rand() direction for rand() distance?
	// -SB
	/*
	Position pos = mobileEntity->getPosition();
	std::vector<Direction> openDirections = checkArea(mobileEntity->getPosition());
	pos.move(openDirections.at(rand() % openDirections.size()));
	mobileEntity->setPosition(pos);
	*/
}
void Creature::attack()
{
	// Detect entities in range
	// Wolves and orges attack everything not hostile
	// -SB
}

void Creature::flee()
{
	// If Villager, Wolf, Orge in range flee opposite direction
	// Deer

}
void Creature::update()
{
	for (int i = 0; i < creatureList.size(); i++)
		decideAction(creatureList.at(i));
}
MobileEntityReference Creature::getACreature()
{
	// Redundant function - will remove
	return creatureList.at(0);
}
