#pragma once

#include <vector>
#include "entity.h"


class WorldObserver
{
	WorldReference world;
	int worldSize;
	bool checkBounds(int x, int y);
	void setWorldSize(int);
	void fill(EntityType);

public:
	void registerWorld(World&);
	void prepareWorld(int);
	EntityType get(Position);
	EntityType get(int x, int y);
	void change(EntityType, Position);
	void change(EntityType, int x, int y);
	int getWorldSize() {	return worldSize;	};
};

typedef std::vector<std::vector<EntityType>> World;
typedef World * WorldReference;