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

Direction* parseDirection(Direction direction)
{
	Direction directionArray[2];
	directionArray[0] = directionArray[1] = 0;
	int i = 0;
	if (direction & D_UP) { directionArray[i] = D_UP; i++; }
	if (direction & D_DOWN) { directionArray[i] = D_DOWN; i++; }
	if (direction & D_LEFT) { directionArray[i] = D_LEFT; i++; }
	if (direction & D_RIGHT) { directionArray[i] = D_RIGHT; i++; }
	return directionArray;
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

Position Pathfinding::getNeighbor(Position pos, Direction direction)
{
	Position neighbor(pos);
	neighbor.move(direction);
	return neighbor;
}

NodeList* Pathfinding::identifySuccessors(Node* cur, Position start, Position end)
{
	NodeList successors;
	NodeList neighbors;
	neighbors.push_back(cur);
	for (Node* i : neighbors)
	{
		i = jump(cur, direction(cur->pos, i->pos), start, end);
		successors.push_back(i);
	}
	return &successors;
}

Node* Pathfinding::jump(Node* cur, Direction direction, Position start, Position end)
{
	Node neighbor(*cur);
	neighbor.pos.move(direction);
	if (!neighbor.pos.checkSanity()) // check obstruction
		return NULL;
	if (neighbor.pos == end)
		return &neighbor;
	if (direction != D_UP &&
		direction != D_DOWN &&
		direction != D_LEFT &&
		direction != D_RIGHT &&
		direction != D_NONE) //direction is diagonal
	{
		Direction* directions = parseDirection(direction);
		for (int i = 0; i < sizeof(directions); i++)
			if (jump(cur, directions[i], start, end) != NULL)
				return &neighbor;
	}
	return jump(cur, direction, start, end);
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
			Node neighborNode(getNeighbor(currentNode->pos, (D_UP & D_RIGHT)), currentNode, calcHeuristicCost(currentNode->pos, goal));
			if (!exists(&closedList, &neighborNode))
			{
				neighborNode.parentNode = currentNode;
				neighborNode.exactCost++;
				neighborNode.finalCost = neighborNode.exactCost + neighborNode.heuristicCost;
				openList.push_back(&neighborNode);
			}
		}
	}
}
