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
	if (cur.getX() > neighbor.getX()) direction |= D_LEFT;
	if (cur.getX() < neighbor.getX()) direction |= D_RIGHT;
	if (cur.getY() > neighbor.getY()) direction |= D_DOWN;
	if (cur.getY() < neighbor.getY()) direction |= D_UP;
	return direction;
}

Direction* Pathfinding::parseDirection(Direction direction)
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
		std::sort(nodeList->begin(), nodeList->end());
		Node* lowestNode = *nodeList->begin();
		nodeList->erase(nodeList->begin());
		return lowestNode;
	}
	return NULL;
}

double Pathfinding::calcHeuristicCost(Position start, Position goal)
{
	//Manhatten calculation
	return abs(start.getX() - goal.getX()) + abs(start.getY() - goal.getY());
}

Position Pathfinding::getNeighbor(Position pos, Direction direction)
{
	Position neighbor(pos);
	neighbor.moveUnchecked(direction);
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

PositionList* Pathfinding::findPath(Position start, Position goal, ObstructionMap obstructionMap)
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
			// Need to use identifySuccessors. 
			// Start node needs to add all directions to search.
			// - Push all directions at beginning or determine from NULL parent
			//
			// Need to finish if statements below from A*. 
			// exactCost needs to be fixed.
			// -? Remove entirely from here and 
			//      move to subfunction dealing with neighbors
			// -? Make grid dealing with all costs
			// -? exactCost = distance using vectors
			//
			// -SB, 2014.09.05

			// use or and and
			// Will refactor
			Position curPos = currentNode->pos;
			NodeList neighborList;
			Node* nodelist[8];
			nodelist[0] = &Node(getNeighbor(curPos, D_UP), currentNode, calcHeuristicCost(curPos, goal));
			nodelist[1] = (&Node(getNeighbor(curPos, D_DOWN), currentNode, calcHeuristicCost(curPos, goal)));
			nodelist[2] = (&Node(getNeighbor(curPos, D_LEFT), currentNode, calcHeuristicCost(curPos, goal)));
			nodelist[3] = (&Node(getNeighbor(curPos, D_RIGHT), currentNode, calcHeuristicCost(curPos, goal)));
			nodelist[4] = (&Node(getNeighbor(curPos, D_UP & D_LEFT), currentNode, calcHeuristicCost(curPos, goal)));
			nodelist[5] = (&Node(getNeighbor(curPos, D_UP & D_RIGHT), currentNode, calcHeuristicCost(curPos, goal)));
			nodelist[6] = (&Node(getNeighbor(curPos, D_DOWN & D_LEFT), currentNode, calcHeuristicCost(curPos, goal)));
			nodelist[7] = (&Node(getNeighbor(curPos, D_DOWN & D_RIGHT), currentNode, calcHeuristicCost(curPos, goal)));
			for (int i = 0; i < 8; i++)
			{
				if (nodelist[i]->pos.checkSanity())
					neighborList.push_back(nodelist[i]);
			}

			for (Node* neighbor : neighborList)
			{
				if (!exists(&closedList, neighbor))
				{
					neighbor->parentNode = currentNode;
					neighbor->exactCost++;
					neighbor->finalCost = neighbor->exactCost + neighbor->heuristicCost;
					openList.push_back(neighbor);
				}
			}

			// Testing A* for now
			/*
			NodeList* succList = identifySuccessors(currentNode, start, goal);
			for (Node* succ : *succList)
			{
				Node neighborNode(getNeighbor(currentNode->pos, (D_UP & D_RIGHT)), currentNode, calcHeuristicCost(currentNode->pos, goal));
				if (!exists(&closedList, &neighborNode))
				{
					neighborNode.parentNode = currentNode;
					neighborNode.exactCost++;
					neighborNode.finalCost = neighborNode.exactCost + neighborNode.heuristicCost;
					openList.push_back(&neighborNode);
				}
			}
			*/
		}
	}
	return constructPath(currentNode);
}

PositionList* Pathfinding::constructPath(Node* goal)
{
	Node* node = goal;
	PositionList path;
	std::cout << "(" << node->pos.getX() << ", " << node->pos.getY() << "), ";
	while (node->parentNode != NULL)
	{
		//
		// ? Include orginal position
		//

		path.push_back(node->pos);
	}
	std::reverse(path.begin(), path.end());
	return &path;
}