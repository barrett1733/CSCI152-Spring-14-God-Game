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
	EntityType getEntityTypeAt(Position);
	EntityType getEntityTypeAt(int x, int y);
	void changeEntityTypeAt(EntityType, Position);
	void changeEntityTypeAt(EntityType, int x, int y);
	int getWorldSize() {	return worldSize;	};
};

typedef std::vector<std::vector<EntityType>> World;
typedef World * WorldReference;