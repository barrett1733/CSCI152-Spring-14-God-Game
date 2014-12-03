#include "pathfinding.h"

double Pathfinding::pathCost(Direction dir)
{
	if (dir >= D_NORTH_EAST)
		return intercardinalNeighbor;
	else
		return cardinalNeighbor;
}

PositionList Pathfinding::findPath(Position start, Position goal, ObstructionMap* obstructionMap)
{
	goalReached = false;
	searchCounter = 0;

	indexGraph.set(start, NULL, 0, DiagonalDistance(neighborPos, goal));

	searchList.push(&indexGraph[start]);

	closestToGoalNode = &indexGraph[start];
	curNode = NULL;

	while (!goalReached && (!searchLimiter || searchCounter <= searchMax))
	{
		searchCounter++;

		if (searchList.empty())
			return constructPath(closestToGoalNode);

		curNode = searchList.pop();

		// this is questionable
		if (curNode->fcost < closestToGoalNode->fcost)
			closestToGoalNode = curNode;

		if (curNode->pos == goal)
		{
			goalReached = true;
		}
		else
		{
			for (Direction dir = D_NORTH; dir < D_COUNT; dir++)
			{
				neighborPos = curNode->pos;
				neighborPos.moveUnchecked(dir);
				if (neighborPos.checkSanity() && obstructionMap->isOpen(neighborPos))
				{
					if (indexGraph.exists(neighborPos))
					{
						if (curNode->gcost < indexGraph[neighborPos].gcost)
						{
							indexGraph[neighborPos].gcost = curNode->gcost;
							indexGraph[neighborPos].fcost = indexGraph[neighborPos].gcost + DiagonalDistance(neighborPos, goal);
							indexGraph[neighborPos].parentNode = curNode;
						}
					}
					else
					{
						indexGraph.set(
							neighborPos,
							curNode,
							curNode->gcost + EuclideanDistance(curNode->pos, neighborPos),
							curNode->gcost + EuclideanDistance(curNode->pos, neighborPos) + DiagonalDistance(neighborPos, goal)
							);
						searchList.push(&indexGraph[neighborPos]);
					}
				}
			}
		}
	}
	return constructPath(curNode);
}

// Does not include original position
PositionList Pathfinding::constructPath(Node* goal)
{
	Node* node = goal;
	PositionList path;
	path.reserve(Position::max_x * Position::max_y);

	if (node->parentNode == NULL)
	{
		path.push_back(node->pos);
		return path;
	}

	while (node->parentNode != NULL)
	{
		path.push_back(node->pos);
		node = node->parentNode;
	}
	std::reverse(path.begin(), path.end());

	searchList.clear();
	indexGraph.clear();
	return path;
}

Position Pathfinding::findNextPosition(Position start, Position goal, ObstructionMapReference obstructionMap)
{
	return findPath(start, goal, obstructionMap)[0];
}