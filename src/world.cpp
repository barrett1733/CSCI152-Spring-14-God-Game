#include "world.h"

bool WorldObserver::checkBounds(int x, int y)
{
	if (x >= 0 && x < worldSize && y >= 0 && y < worldSize)
		return true;
	return false;
}
void WorldObserver::setWorldSize(int worldSize)
{
	this->worldSize = worldSize;
}
void WorldObserver::fill(EntityType entityType)
{

	for (int i = 0; i < worldSize; i++)
	for (int j = 0; j < worldSize; i++)
		world->at(i).at(j) = entityType;

}

void WorldObserver::registerWorld(World &worldMap)
{
	world = &worldMap;
}
void WorldObserver::prepareWorld(int worldSize)
{
	setWorldSize(worldSize);
	world->resize(worldSize);
	fill(ET_NONE);
}
EntityType WorldObserver::get(Position position)
{
	return get(position.getX(),position.getY());
}
EntityType WorldObserver::get(int x, int y)
{
	if (checkBounds(x,y))
		return world->at(x).at(y);
}
void WorldObserver::change(EntityType entityType, Position position)
{
	change(entityType, position.getX(), position.getY());
}
void WorldObserver::change(EntityType entityType, int x, int y)
{
	world->at(x).at(y) = entityType;
}
