#include "pathfinding.h"

double Pathfinding::calcHCost(Position start, Position goal)
{
	//Manhatten calculation
	double cost = abs(start.getX() - goal.getX()) + abs(start.getY() - goal.getY());
	return cost;
}

Position Pathfinding::getNeighbor(Position pos, Direction direction)
{
	Position newpos(pos);
	newpos.moveUnchecked(direction);
	return newpos;
}

void Pathfinding::populateNeighbors(Position pos)
{
	neighborArray[0] = Neighbor(getNeighbor(pos, D_UP), cardinalNeighbor);
	neighborArray[1] = Neighbor(getNeighbor(pos, D_DOWN), cardinalNeighbor);
	neighborArray[2] = Neighbor(getNeighbor(pos, D_LEFT), cardinalNeighbor);
	neighborArray[3] = Neighbor(getNeighbor(pos, D_RIGHT), cardinalNeighbor);
	neighborArray[4] = Neighbor(getNeighbor(pos, D_UP | D_LEFT), intercardinalNeighbor);
	neighborArray[5] = Neighbor(getNeighbor(pos, D_UP | D_RIGHT), intercardinalNeighbor);
	neighborArray[6] = Neighbor(getNeighbor(pos, D_DOWN | D_LEFT), intercardinalNeighbor);
	neighborArray[7] = Neighbor(getNeighbor(pos, D_DOWN | D_RIGHT), intercardinalNeighbor);
}

PositionList Pathfinding::findPath(Position start, Position goal, ObstructionMap* obstructionMap)
{
	goalReached = false;

	Node* startNode = new Node(start, NULL, 0, calcHCost(start, goal));

	searchList.push(startNode);
	
	indexGraph.assign(startNode);

	Node* curNode = NULL;

	while (!goalReached)
	{
		if (searchList.empty())
			return constructPath(startNode);

		curNode = searchList.pop();

		if (curNode->pos == goal)
		{
			goalReached = true;
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				populateNeighbors(curNode->pos);
				if (neighborArray[i].first.checkSanity() && obstructionMap->isOpen(neighborArray[i].first))
				{
					if (&indexGraph[neighborArray[i].first] != NULL)
					{
						Node* temp = &indexGraph[neighborArray[i].first];
						if (curNode->gcost < temp->gcost)
						{
							temp->gcost = curNode->gcost;
							temp->fcost = temp->gcost + temp->hcost;
							temp->parentNode = curNode;
						}
					}
					else
					{
						Node* newNeighbor = new Node(
							neighborArray[i].first,
							curNode,
							curNode->gcost + neighborArray[i].second,
							calcHCost(neighborArray[i].first, goal)
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