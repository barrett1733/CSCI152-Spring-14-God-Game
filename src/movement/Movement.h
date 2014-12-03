#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "distance.h"
#include "../entity.h"

class Movement
{
const static int inf = 999999;
public:
	static void moveMobileEntity(MobileEntity* entity, ObstructionMap* obsMap);
	static Position moveTowardsTarget(MobileEntity* entity, ObstructionMap* obsMap);
	static Position moveAwayFromTarget(MobileEntity* entity, ObstructionMap* obsMap);
	static double evaluateScore(MobileEntity* entity, Position nextPos, ObstructionMap* obsMap);

};

#endif