#include "pathfinding.h"


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

	Node* startNode = new Node(start, NULL, 0, calcHCost(start, goal));
	searchList.push_back(startNode);
	indexList.push_back(startNode);

	Node* curNode = NULL;

	while (!goalReached)
	{
		if (searchList.empty())
			return constructPath(startNode);

		//std::cout << std::endl;
		curNode = searchList.pop();

		if (curNode == NULL)
		{
			std::cout << "Pathfinding Error - curNode == NULL" << std::endl;
			break;
		}
		
		//std::cout << "- " << *curNode << std::endl;

		if (curNode->pos == goal)
		{
			goalReached = true;
		}
		else
		{
			typedef std::pair<Position, double> neighborTuple;
			neighborTuple neighborPos[8]; // Should never be anymore than 8 neighbors
			neighborPos[0] = neighborTuple(getNeighbor(curNode->pos, D_UP), cardinalNeighbor);
			neighborPos[1] = neighborTuple(getNeighbor(curNode->pos, D_DOWN), cardinalNeighbor);
			neighborPos[2] = neighborTuple(getNeighbor(curNode->pos, D_LEFT), cardinalNeighbor);
			neighborPos[3] = neighborTuple(getNeighbor(curNode->pos, D_RIGHT), cardinalNeighbor);
			neighborPos[4] = neighborTuple(getNeighbor(curNode->pos, D_UP | D_LEFT), intercardinalNeighbor);
			neighborPos[5] = neighborTuple(getNeighbor(curNode->pos, D_UP | D_RIGHT), intercardinalNeighbor);
			neighborPos[6] = neighborTuple(getNeighbor(curNode->pos, D_DOWN | D_LEFT), intercardinalNeighbor);
			neighborPos[7] = neighborTuple(getNeighbor(curNode->pos, D_DOWN | D_RIGHT), intercardinalNeighbor);

			for (int i = 0; i < 8; i++)
			{
				if (neighborPos[i].first.checkSanity() && obstructionMap.isOpen(neighborPos[i].first))
				{
					if (indexList.exists(neighborPos[i].first))
					{
						Node* temp = indexList.find(neighborPos[i].first);
						if (curNode->gcost < temp->gcost)
						{
							//std::cout << "> " << neighborPos[i].first << " G:" << temp->gcost << " | " << curNode->gcost << std::endl;
							temp->gcost = curNode->gcost;
							temp->fcost = temp->gcost + temp->hcost;
							temp->parentNode = curNode;
						}
					}
					else if (!indexList.exists(neighborPos[i].first))
					{
						Node* newNeighbor = new Node(
							neighborPos[i].first, 
							curNode, 
							curNode->gcost + neighborPos[i].second, 
							calcHCost(neighborPos[i].first, goal)
							);
						//std::cout << "+ " << *newNeighbor << std::endl;
						searchList.push_back(newNeighbor);
						indexList.push_back(newNeighbor);
					}
				}
			}
		}
	}
	return constructPath(curNode);
}

// Does not include original position
PositionList* Pathfinding::constructPath(Node* goal)
{
	Node* node = goal;
	PositionList path;
	while (node->parentNode != NULL)
	{
		path.push_back(node->pos);
		node = node->parentNode;
		//std::cout << node->pos << ", ";
	}
	std::reverse(path.begin(), path.end());
	for (Position pos : path)
		std::cout << pos << ", ";
	std::cout << std::endl;
	indexList.destroy();
	return &path;
}