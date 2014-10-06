#ifndef PATHFINDING_H_
#define PATHFINDING_H_
/*
Jump Point Search Code:
https://code.google.com/p/ddh/

Jump Point Search Paper:
http://www.aaai.org/ocs/index.php/AAAI/AAAI11/paper/viewFile/3761/4007

Jump Point Search Explaination:
http://harablog.wordpress.com/2011/09/07/jump-point-search/

Jump Point Search Demo (Other searches included):
http://qiao.github.io/PathFinding.js/visual/

*/

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>
#include "obstruction-map.h"

struct Node {
	Position pos;
	Node* parentNode;
	double gcost, hcost, fcost;
	Node(Position pos, Node* parent, double g, double h) :
		pos(pos),
		parentNode(parent),
		gcost(g),
		hcost(h),
		fcost(g+h)
	{}
	bool operator== (Node &a) const
	{
		return (pos == a.pos &&
			parentNode == a.parentNode &&
			gcost == a.gcost &&
			hcost == a.hcost &&
			fcost == a.fcost);
	}
	Node& operator= (Node& a)
	{
		pos = a.pos;
		parentNode = a.parentNode;
		gcost = a.gcost;
		hcost = a.hcost;
		fcost = a.fcost;
		return *this;
	}
};

typedef std::vector<Node*> NodeList;
typedef std::vector<Node*>::iterator NodeListIter;
typedef std::vector<Position> PositionList;
#define cardinalNeighbor 5
#define intercardinalNeighbor 7

class Pathfinding
{
	typedef bool(Pathfinding::*compareNodeFn) (Node*, Node*);

	NodeList openList;
	bool goalReached;

	bool exists(NodeList*, Node*);
	Direction direction(Position, Position);
	Direction* parseDirection(Direction);

	bool remove(Node*);
	Node* compareNodes(compareNodeFn);
	Node* find(compareNodeFn, Node*);

	double calcHCost(Position start, Position goal);
	Position getNeighbor(Position, Direction);
	PositionList* constructPath(Node*);

	NodeList* identifySuccessors(Node* cur, Position start, Position end);
	Node* jump(Node* cur, Direction direction, Position start, Position end);


	bool lessThanGcost(Node* a, Node* b) { return a->gcost < b->gcost; }
	bool equals(Node*a, Node* b) { return *a == *b; }
	bool equalsPos(Node*a, Node* b) { return a->pos == b->pos; }


public:
	PositionList* findPath(Position start, Position goal, ObstructionMap obstructionMap);

};


#endif
