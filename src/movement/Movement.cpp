#include "Movement.h"

double Movement::evaluateScore(MobileEntity* entity, Position nextPos, ObstructionMap* obsMap)
{
	double score = 0;
	Position pos = entity->getPosition();
	Position target = entity->getTarget()->getPosition();
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
	}
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

