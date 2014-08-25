#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include "obstruction-map.h"

struct Node {
	Position pos;
	Node* parentNode;
	double exactCost, heuristicCost, finalCost;
	Node(Position pos, Node* parent, double hCost) :
		pos(pos),
		parentNode(parent),
		exactCost(0),
		heuristicCost(hCost),
		finalCost(0)
	{}
};

typedef std::vector<Node*> NodeList;
typedef std::vector<Node*>::iterator NodeListIter;
#define standardNeighbor 5
#define diagonalNeighbor 7


class Pathfinding
{
	NodeList* findPath(Position start, Position goal, ObstructionMap obstructionMap);

private:

	NodeList openList;
	NodeList closedList;
	bool goalReached;

	
	bool exists(NodeList*, Node*);
	Direction direction(Position, Position);
	Direction* parseDirection(Direction);
	Node* findLowestFCostNode(NodeList* nodeList);
	double calcHeuristicCost(Position start, Position goal);
	Position getNeighbor(Position,Position);
	NodeList* identifySuccessors(Node* cur, Position start, Position end);
	Node* jump(Node* cur, Direction direction, Position start, Position end);
};


#endif
