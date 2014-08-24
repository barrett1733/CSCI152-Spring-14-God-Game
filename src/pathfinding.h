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

class Pathfinding
{
	NodeList* findPath(Position start, Position goal, ObstructionMap obstructionMap);

private:

	NodeList openList;
	NodeList closedList;

	bool exists(NodeList*, Node*);
	Node* findLowestFCostNode(NodeList* nodeList);
};


#endif
