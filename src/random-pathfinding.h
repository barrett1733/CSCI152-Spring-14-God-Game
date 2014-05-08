#ifndef RANDOM_PATHFINDING_H_
#define RANDOM_PATHFINDING_H_

#include <iostream>
#include <vector>
#include "world-gen.h"
#include "obstruction-map.h"

class RandomPathfinding{
	Direction determineDirection(Position source, Position target);
	// TODO: finish these two functions
	Direction randomDirection(Position source);
	Direction invertDirection(Direction source);
public:
	Position moveTowardsTarget(MobileEntityReference, Position);
	Position moveTowardsTarget(MobileEntityReference, MobileEntityReference);
	Position moveAwayFromTarget(MobileEntityReference, Position);
	Position moveAwayFromTarget(MobileEntityReference, MobileEntityReference);
	Position moveRandomly(MobileEntityReference);
};


#endif



