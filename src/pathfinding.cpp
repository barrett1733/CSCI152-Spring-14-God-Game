#include "pathfinding.h"

void Pathfinder::addToWanderList(MobileEntityReference mobileEntity)
{
	thingsToWander.push_back(mobileEntity);
}
void Pathfinder::removeFromWanderList(MobileEntityReference mobileEntity)
{
	for (int i = 0; i < thingsToWander.size(); i++)
		if (thingsToWander.at(i) == mobileEntity)
			thingsToWander.erase(thingsToWander.begin() + i);
}
void Pathfinder::wander()
{
	Position pos;
	std::vector<Direction> openDirections;
	for (int i = 0; i < thingsToWander.size(); i++)
	{
		pos = thingsToWander.at(i)->getPosition();
		openDirections = checkArea(pos);
		pos.move(openDirections.at(rand() % openDirections.size()));
		thingsToWander.at(i)->setPosition(pos);
	}
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
