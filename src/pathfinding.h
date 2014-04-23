#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <iostream>
#include <vector>
#include "world-gen.h"

using namespace std;


class Pathfinder{
	std::vector<Direction> checkArea(Position);
	int mapDirectionX(Direction direction);
	int mapDirectionY(Direction direction);
	bool checkDirection(Position position, Direction direction);
	Direction determineDirection(Position me, Position target);
public:
	WorldGeneration * world;
	Direction moveTowardsTarget(MobileEntityReference, Position);
	Direction moveTowardsTarget(MobileEntityReference, MobileEntityReference);
};


#endif



