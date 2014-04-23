#include "pathfinding.h"

Direction Pathfinder::determineDirection(Position me, Position target)
{
	if (me.getY() < target.getY())
		return D_DOWN;
	if (me.getY() > target.getY())
		return D_UP;
	if (me.getY() == target.getY())
	{
		if (me.getX() < target.getX())
			return D_RIGHT;
		if (me.getX() > target.getX())
			return D_LEFT;
	}
	return D_NONE;
}
void Pathfinder::moveTowardsTarget(MobileEntityReference me, Position target)
{
	Position pos = me->getPosition();
	pos.move(determineDirection(pos, target));
	me->setPosition(pos);
}
void Pathfinder::moveTowardsTarget(MobileEntityReference me, MobileEntityReference target)
{
	moveTowardsTarget(me, target->getPosition());
}

std::vector<Direction> Pathfinder::checkArea(Position position)
{
	std::vector<Direction> openDirections;
	if (checkDirection(position, D_UP))
		openDirections.push_back(D_UP);
	if (checkDirection(position, D_RIGHT))
		openDirections.push_back(D_RIGHT);
	if (checkDirection(position, D_DOWN))
		openDirections.push_back(D_DOWN);
	if (checkDirection(position, D_LEFT))
		openDirections.push_back(D_LEFT);
	openDirections.push_back(D_NONE);
	return openDirections;
}
int Pathfinder::mapDirectionX(Direction dir)
{
	if (dir & D_RIGHT)		return 1;
	if (dir & D_UP_RIGHT)	return 1;
	if (dir & D_DOWN_RIGHT) return 1;
	if (dir & D_LEFT)		return -1;
	if (dir & D_UP_LEFT)	return -1;
	if (dir & D_DOWN_LEFT)  return -1;
	if (dir & D_NONE)		return 0;
}
int Pathfinder::mapDirectionY(Direction dir)
{
	if (dir & D_UP)			return -1;
	if (dir & D_UP_RIGHT)	return -1;
	if (dir & D_UP_LEFT)	return -1;
	if (dir & D_DOWN)		return 1;
	if (dir & D_DOWN_RIGHT) return 1;
	if (dir & D_DOWN_LEFT)  return 1;
	if (dir & D_NONE)		return 0;
}
bool Pathfinder::checkDirection(Position pos, Direction dir)
{
	if (world->world_positions[pos.getX() + mapDirectionX(dir)][pos.getY() + mapDirectionY(dir)] == ET_NONE)
		return true;
	return false;
}
