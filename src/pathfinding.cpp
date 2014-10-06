#include "pathfinding.h"

bool Pathfinding::exists(Node* node)
{
	if (find(&Pathfinding::equalNode, node) != NULL)
		return true;
	else
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

bool Pathfinding::remove(Node* a)
{
	if (!openList.empty())
	{	
		int i = 0;
		while (i < openList.size())
		{
			if (*a == *openList[i])
				openList.erase(openList.begin()+i);
			i++;
		}
		return true;
	}
	return false;
}

Node* Pathfinding::compareNodes(compareNodeFn compare)
{
	if (!openList.empty())
	{
		Node* match = *openList.begin();
		for (Node* node : openList)
		if ((this->*compare)(match, node))
			match = node;
		return match;
	}
	return NULL;
}

Node* Pathfinding::find(compareNodeFn compare, Node* a)
{
	if (!openList.empty())
	{
		Node* match = *openList.begin();
		for (Node* node : openList)
		if ((this->*compare)(a, node))
			match = node;
		return match;
	}
	return NULL;
}

double Pathfinding::calcHCost(Position start, Position goal)
{
	//Manhatten calculation
	return abs(start.getX() - goal.getX()) + abs(start.getY() - goal.getY());
}

Position Pathfinding::getNeighbor(Position pos, Direction direction)
{
	pos.moveUnchecked(direction);
	return pos;
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

	Node startNode(start, NULL, 0, calcHCost(start, goal));
	openList.push_back(&startNode);

	Node* curNode = NULL;

	while (!goalReached)
	{
		//currentNode points to itself
		curNode = compareNodes(&Pathfinding::lessThanGcost);
		
		if (curNode == NULL)
		{
			std::cout << "Pathfinding error" << std::endl;
			break;
		}
		remove(curNode);

		if (curNode->pos == goal)
		{
			goalReached = true;
		}
		else
		{
			// object removed in findlowest fcost
			//openList.erase(std::find(openList.begin(), openList.end(), currentNode));

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

			// Will refactor to for loop

			NodeList neighborList;
			Node* nodelist[8];
			nodelist[0] = &Node(getNeighbor(curNode->pos, D_UP), curNode, curNode->gcost+1, calcHCost(curNode->pos, goal));
			nodelist[1] = &Node(getNeighbor(curNode->pos, D_DOWN), curNode, curNode->gcost+1, calcHCost(curNode->pos, goal));
			nodelist[2] = &Node(getNeighbor(curNode->pos, D_LEFT), curNode, curNode->gcost+1, calcHCost(curNode->pos, goal));
			nodelist[3] = &Node(getNeighbor(curNode->pos, D_RIGHT), curNode, curNode->gcost+1, calcHCost(curNode->pos, goal));

			// diagonals need to be handled differently
			nodelist[4] = &Node(getNeighbor(curNode->pos, D_UP | D_LEFT), curNode, curNode->gcost+1, calcHCost(curNode->pos, goal));
			nodelist[5] = &Node(getNeighbor(curNode->pos, D_UP | D_RIGHT), curNode, curNode->gcost+1, calcHCost(curNode->pos, goal));
			nodelist[6] = &Node(getNeighbor(curNode->pos, D_DOWN | D_LEFT), curNode, curNode->gcost+1, calcHCost(curNode->pos, goal));
			nodelist[7] = &Node(getNeighbor(curNode->pos, D_DOWN | D_RIGHT), curNode, curNode->gcost+1, calcHCost(curNode->pos, goal));

			for (int i = 0; i < 4; i++) // diagonal searching removed for now
			{
				Position pos = nodelist[i]->pos;
				//if (pos.getX() >= 0 && pos.getY() >= 0 && pos.getX() <= 10 && pos.getY() <= 10)
				if (pos.checkSanity())
					if (!exists(nodelist[i]))
					{
						openList.push_back(nodelist[i]);
					}
					else if (exists(nodelist[i]))
					{
						//something wrong here - maybe not
						Node* existingNode = find(&Pathfinding::equalPos, nodelist[i]);
						if (existingNode->gcost > nodelist[i]->gcost)
							*existingNode = *nodelist[i];
							//openList.push_back(nodelist[i]);
					}
			}

			// Testing A* for now
			/*
			NodeList* succList = identifySuccessors(currentNode, start, goal);
			for (Node* succ : *succList)
			{
				Node neighborNode(getNeighbor(currentNode->pos, (D_UP & D_RIGHT)), currentNode, calcHCost(currentNode->pos, goal));
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
	return constructPath(curNode);
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