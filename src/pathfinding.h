#ifndef PATHFINDING_H_
#define PATHFINDING_H_
/*
Jump Point Search Code:
https://code.google.com/p/ddh/

Jump Point Search Paper:
http://www.aaai.org/ocs/index.php/AAAI/AAAI11/paper/viewFile/3761/4007

Jump Point Search Explaination:
http://harablog.wordpress.com/2011/09/07/jump-point-search/

*/

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
#define cardinalNeighbor 5
#define intercardinalNeighbor 7


class Pathfinding
{
	NodeList* findPath(Position start, Position goal, ObstructionMap obstructionMap);

private:

	NodeList openList;
	NodeList closedList;
	bool goalReached;

	
	bool exists(NodeList*, Node*);
	Direction direction(Position, Position);
	Direction jumpDirections(Direction);
	Node* findLowestFCostNode(NodeList* nodeList);
	double calcHeuristicCost(Position start, Position goal);
	Position getNeighbor(Position,Direction);
	NodeList* identifySuccessors(Node* cur, Position start, Position end);
	Node* jump(Node* cur, Direction direction, Position start, Position end);
};


#endif
