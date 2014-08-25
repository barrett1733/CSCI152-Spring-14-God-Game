#include "pathfinding.h"

bool Pathfinding::exists(NodeList* nodeList, Node* node)
{
	for (Node* i : *nodeList)
		if (i == node)
			return true;
	return false;
}

Direction Pathfinding::direction(Position cur, Position neighbor)
{
	int direction = 0;
	if (cur.getX() > neighbor.getX()) direction & D_DOWN;
	if (cur.getX() < neighbor.getX()) direction & D_UP;
	if (cur.getY() > neighbor.getY()) direction & D_RIGHT;
	if (cur.getY() < neighbor.getY()) direction & D_LEFT;
	return direction;
}

Node* Pathfinding::findLowestFCostNode(NodeList* nodeList)
{
	if (!nodeList->empty())
	{
		Node* lowestNode = nodeList->at(0);
		for (Node* i : *nodeList)
		if (i->finalCost < lowestNode->finalCost)
			lowestNode = i;
		return lowestNode;
	}
	return NULL;
}

double Pathfinding::calcHeuristicCost(Position start, Position goal)
{
	//Eucildian calculation
	return sqrt(pow((start.getX() - goal.getX()), 2) + pow((start.getY() - goal.getY()), 2));
}

Position Pathfinding::getNeighbor(Position pos, Position direction)
{
	Position neighbor(pos);
	neighbor.set(direction);
	return neighbor;
}

NodeList* Pathfinding::identifySuccessors(Node* cur, Position start, Position end)
{
	NodeList successors;
	NodeList neighbors;
	neighbors.push_back(cur);
	for (Node* i : neighbors)
	{
		i = jump(cur, direction(cur, i), start, end);
		successors.push_back(i);
	}
	return &successors;
}

Node* Pathfinding::jump(Node* cur, Position direction, Position start, Position end)
{
	/*
	Node n = step(cur,direction)  ?? getNeighbor
	if( n = obstructed or checksanity fails)
		return null;
	if ( n = g)
		return n
	if direction = diagonal
		for all directions i
			if jump (cur, i, start, end) != null
				return n
	return jump (cur, direction, start, end)
	*/
}


NodeList* Pathfinding::findPath(Position start, Position goal, ObstructionMap obstructionMap)
{
	goalReached = false;

	Node startNode(start, NULL, calcHeuristicCost(start, goal));
	openList.push_back(&startNode);

	Node* currentNode = NULL;

	while (!goalReached)
	{
		currentNode = findLowestFCostNode(&openList);
		if (currentNode == NULL)
		{
			std::cout << "Pathfinding error" << std::endl;
			break;
		}

		closedList.push_back(currentNode);

		if (currentNode->pos == goal)
		{
			goalReached = true;
		}
		else
		{
			openList.erase(std::find(openList.begin(), openList.end(), currentNode));
			//find Neighbors
			for (int i = N_UP; i < N_COUNT; i++)
			{
				Node neighborNode(getNeighbor(currentNode->pos, i), currentNode, calcHeuristicCost(currentNode->pos, goal));
				if (exists(&closedList, &neighborNode))
				{
					neighborNode.parentNode = currentNode;
					if (i % 2 == 0)
						neighborNode.exactCost = currentNode->exactCost + standardNeighbor;
					else
						neighborNode.exactCost = currentNode->exactCost + diagonalNeighbor;

					neighborNode.finalCost = neighborNode.exactCost + neighborNode.heuristicCost;
				}
				else if (!exists(&openList, &neighborNode))
				{
					neighborNode.parentNode = currentNode;
					neighborNode.exactCost++;
					neighborNode.finalCost = neighborNode.exactCost + neighborNode.heuristicCost;
				}
				else
				{
					neighborNode.parentNode = currentNode;
					neighborNode.exactCost++;
					neighborNode.finalCost = neighborNode.exactCost + neighborNode.heuristicCost;
				}
			}
		}
	}
}
