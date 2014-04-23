#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <iostream>
#include <vector>
#include "world-gen.h"

using namespace std;


class Pathfinder{
	int mapDirectionX(Direction direction);
	int mapDirectionY(Direction direction);
	bool checkDirection(Position position, Direction direction);
	Direction determineDirection(Position me, Position target);
public:
	WorldGeneration * world;
	std::vector<Direction> checkArea(Position);
	Direction moveTowardsTarget(MobileEntityReference, Position);
	Direction moveTowardsTarget(MobileEntityReference, MobileEntityReference);
};


#endif



