#include "pathfinding.h"

bool Pathfinding::exists(NodeList* nodeList, Node* node)
{
	for (int i = 0; i < nodeList->size(); i++)
		if (nodeList->at(i) == node)
			return true;
	return false;
}

Node* Pathfinding::findLowestFCostNode(NodeList* nodeList)
{
	if (!nodeList->empty())
	{
		Node* lowestNode = nodeList->at(0);
		for (int i = 0; i < nodeList->size(); i++)
		if (nodeList->at(i)->finalCost < lowestNode->finalCost)
			lowestNode = nodeList->at(i);
		return lowestNode;
	}
	return NULL;
}

double Pathfinding::calculateHeuristicCost(Position start, Position goal)
{
	//Eucildian calculation
	return sqrt(pow((start.getX() - goal.getX()), 2) + pow((start.getY() - goal.getY()), 2));
}

NodeList* Pathfinding::findPath(Position start, Position goal, ObstructionMap obstructionMap)
{
	double heuristicCost = calculateHeuristicCost(start,goal);

	goalReached = false;

	Node startNode(start, NULL, heuristicCost);
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
		else
		{
			if (currentNode->pos == goal)
			{
				goalReached = true;
			}
			else
			{
				closedList.push_back(currentNode);
				openList.erase(std::find(openList.begin(), openList.end(), currentNode));

				//find Neighbors
				for (int x = -1; x <= 1; x++)
				for (int y = -1; y <= 1; y++)
				{
					Node neighborNode(Position(currentNode->pos.getX() + x, currentNode->pos.getY() + y), currentNode, heuristicCost);
					if (!exists(&closedList, &neighborNode))
					{
						neighborNode.parentNode = currentNode;
						neighborNode.exactCost++;
						neighborNode.finalCost = neighborNode.exactCost + neighborNode.heuristicCost;
					}
				}
			}
		}
	}
}
