#include "Movement.h"

void Movement::moveMobileEntity(MobileEntity* entity, ObstructionMap* obsMap)
{
	// Find by position 
	// ^ rewrite findpath to work in steps
	// ^ depth first search might be better
	// ^ a* jumps around - need traversal backwards and forwards
	// ^ heuristic might not be needed beyond distance to target
	//
	// 
	// Find by entity type (ie. tree, stone, deer, etc)
	// ^ questionable
	// ^ pair position and entity pointer
	// ^ need access to entity list

	Position currentPos = entity->getPosition();
	Position targetPos = entity->getTarget()->getPosition();
	Position nextPos = Movement::moveTowardsTarget(entity, obsMap);
	Position newPos = entity->moveOnPath(currentPos, nextPos, targetPos);

	obsMap->set(currentPos, OT_EMPTY);

	if (!obsMap->isConsidered(nextPos))
		entity->setPosition(newPos);

	obsMap->set(currentPos, OT_CONSIDERED);

}

double Movement::evaluateScore(MobileEntity* entity, Position nextPos, ObstructionMap* obsMap)
{
	double score = 0;
	Position pos = entity->getPosition();
	Position target = entity->getTarget()->getPosition();
	/*
	switch (entity->pathMap[nextPos])
	{
	case PathMemory::PathMapState::VISITED:
		score -= 1;
		break;
	case PathMemory::PathMapState::UNKNOWN:
		score += 5;
		break;
	case PathMemory::PathMapState::OBSERVED:
		score += 1;
		break;
	}*/
	score += EuclideanDistance(pos, target) - EuclideanDistance(nextPos, target);
	return score;
}


Position Movement::moveTowardsTarget(MobileEntity* entity, ObstructionMap* obsMap)
{
	double bestScore = -inf;
	double score = 0;
	Direction bestDir = D_NONE;
	Position start = entity->getPosition();
	Position neighbor;
	for (int dir = D_NORTH; dir < D_COUNT; dir++)
	{
		neighbor = start.getNeighbor(dir);
		if (obsMap->isOpen(neighbor))
		{
			score = evaluateScore(entity, neighbor, obsMap);
			if (score > bestScore)
			{
				bestScore = score;
				bestDir = dir;
			}
		}
	}
	return start.getNeighbor(bestDir);
}

Position Movement::moveAwayFromTarget(MobileEntity* entity, ObstructionMap* obsMap)
{
	double bestScore = inf;
	double score = 0;
	Direction bestDir = D_NONE;
	Position start = entity->getPosition();
	for (int dir = D_NORTH; dir < D_COUNT; dir++)
	{
		score = evaluateScore(entity, start, obsMap);
		if (score < bestScore)
		{
			bestScore = score;
			bestDir = dir;
		}
	}
	return start.getNeighbor(bestDir);
}

