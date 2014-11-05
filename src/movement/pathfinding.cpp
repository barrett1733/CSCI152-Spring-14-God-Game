#include "pathfinding.h"

double Pathfinding::manhattanDistance(Position start, Position goal)
{
	double cost = abs(start.getX() - goal.getX()) + abs(start.getY() - goal.getY());
	return cost;
}

double Pathfinding::euclideanDistance(Position start, Position goal)
{
	double cost = sqrt(pow((goal.getX() - start.getX()), 2) + pow((goal.getY() - start.getY()), 2));
	return cost;
}

Position Pathfinding::generateNeighbor(Position pos, int index)
{
	Position newpos(pos);
	switch (index)
	{
	case 0: newpos.moveUnchecked(D_UP); break;
	case 1: newpos.moveUnchecked(D_DOWN); break;
	case 2: newpos.moveUnchecked(D_LEFT); break;
	case 3: newpos.moveUnchecked(D_RIGHT); break;
	case 4: newpos.moveUnchecked(D_UP | D_LEFT); break;
	case 5: newpos.moveUnchecked(D_UP | D_RIGHT); break;
	case 6: newpos.moveUnchecked(D_DOWN | D_LEFT); break;
	case 7: newpos.moveUnchecked(D_DOWN | D_RIGHT); break;
	}
	return newpos;
}

Position Pathfinding::getNeighbor(Position pos, Direction dir)
{
	Position newPos(pos);
	newPos.moveUnchecked(dir);
	return newPos;
}

void Pathfinding::populateNeighbors(Position pos)
{
	neighborArray[0] = getNeighbor(pos, D_UP);
	neighborArray[1] = getNeighbor(pos, D_DOWN);
	neighborArray[2] = getNeighbor(pos, D_LEFT);
	neighborArray[3] = getNeighbor(pos, D_RIGHT);
	neighborArray[4] = getNeighbor(pos, D_UP | D_LEFT);
	neighborArray[5] = getNeighbor(pos, D_UP | D_RIGHT);
	neighborArray[6] = getNeighbor(pos, D_DOWN | D_LEFT);
	neighborArray[7] = getNeighbor(pos, D_DOWN | D_RIGHT);
}

PositionList Pathfinding::findPath(Position start, Position goal, ObstructionMap* obstructionMap)
{
	goalReached = false;
	searchCounter = 0;

	startNode = new Node(start, NULL, 0, manhattanDistance(start, goal));

	searchList.push(startNode);
	
	indexGraph.assign(startNode);

	closestToGoalNode = startNode;
	curNode = NULL;

	while (!goalReached && searchCounter <= searchMax)
	{
		searchCounter++;

		if (searchList.empty())
			return constructPath(closestToGoalNode);

		curNode = searchList.pop();

		if (curNode->hcost < closestToGoalNode->hcost)
			closestToGoalNode = curNode;

		if (curNode->pos == goal)
		{
			goalReached = true;
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				// neighbors should equal the amount of of availble neighbors
				// have neighbor function return a pos
				// 
				populateNeighbors(curNode->pos);
				if (neighborArray[i].checkSanity() && obstructionMap->isOpen(neighborArray[i]))
				{
					if (&indexGraph[neighborArray[i]] != NULL)
					{
						temp = &indexGraph[neighborArray[i]];
						if (curNode->gcost < temp->gcost)
						{
							temp->gcost = curNode->gcost;
							temp->fcost = temp->gcost + temp->hcost;
							temp->parentNode = curNode;
						}
					}
					else
					{
						newNeighbor = new Node(
							neighborArray[i],
							curNode,
							curNode->gcost + i<4?cardinalNeighbor:intercardinalNeighbor,
							manhattanDistance(neighborArray[i], goal)
							);
						searchList.push(newNeighbor);
						indexGraph.assign(newNeighbor);
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