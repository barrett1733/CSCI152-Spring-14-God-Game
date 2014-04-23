#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <iostream>
#include <vector>
#include "world-gen.h"

using namespace std;

struct Vehicle
{
	MobileEntityReference mobileEntity;
	Position destination;
	bool reachedDestination = false;
};

class Pathfinder{
	void wander();
public:
	WorldGeneration * world;
	std::vector<Vehicle> thingsToMove;
	std::vector<MobileEntityReference> thingsToWander;
	std::vector<Direction> checkArea(Position);
	int mapDirectionX(Direction direction);
	int mapDirectionY(Direction direction);
	bool checkDirection(Position position, Direction direction);
	void addToWanderList(MobileEntityReference);
	void addToMoveList(MobileEntityReference);
	void removeFromWanderList(MobileEntityReference);
	void removeFromMoveList(MobileEntityReference);
	void moveTowardsTarget(MobileEntityReference, Position);
	void moveTowardsTarget(MobileEntityReference, MobileEntityReference);
};


#endif



