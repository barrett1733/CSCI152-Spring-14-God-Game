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
	Position pos = creature->getPosition();
	std::vector<Direction> openDirections = checkOpenAreas(creature->getPosition());
	pos.move(openDirections.at(rand() % openDirections.size()));
	creature->setPosition(pos);
}
std::vector<Direction> Creature::checkOpenAreas(Position position)
{
	std::vector<Direction> openDirections;
	for (int i = position.getX() - 1; i <= position.getX() + 1; i++)
	{
		for (int j = position.getY() - 1; j <= position.getY() + 1; j++)
			if (i >= 0 && i < world->getWorldSize() && j >= 0 && j < world->getWorldSize())
				if (world->world_positions[i][j] == ET_NONE)
					openDirections.push_back(checkDirection(i, j));
	}
	openDirections.push_back(D_NONE);
	return openDirections;
}
Direction Creature::checkDirection(int i, int j)
{
	if (i  == -1 && j == 0)
		return D_DOWN;
	else if (i  == 0 && j == -1)
		return D_LEFT;
	else if (i  == 1 && j == 0)
		return D_UP;
	else if (i  == 0 && j == 1)
		return D_RIGHT;
	/*
	else if (i == -1 && j == -1)
		return D_DOWN_LEFT;
	else if (i  == -1 && j == 1)
		return D_DOWN_RIGHT;
	else if (i  == 1 && j == -1)
		return D_UP_LEFT;
	else if (i == 1 && j == 1)
		return D_UP_RIGHT;
		*/
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
