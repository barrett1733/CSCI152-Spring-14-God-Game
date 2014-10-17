#ifndef NODE_H_
#define NODE_H_

#include "position.h"
#include <iostream>

#define debug false

struct Node {
	Position pos;
	Node* parentNode;
	bool visited = false;
	double gcost, hcost, fcost;
	Node() :
		pos(Position(0, 0)),
		parentNode(NULL),
		gcost(0),
		hcost(0),
		fcost(0)
	{}
	Node(Position pos, Node* parent, double g, double h) :
		pos(pos),
		parentNode(parent),
		gcost(g),
		hcost(h),
		fcost(g + h)
	{}
	bool operator== (Node &a) const
	{
		return (pos == a.pos &&
			parentNode == a.parentNode &&
			gcost == a.gcost &&
			hcost == a.hcost &&
			fcost == a.fcost &&
			visited == a.visited);
	}
	Node& operator= (Node& a)
	{
		pos = a.pos;
		parentNode = a.parentNode;
		gcost = a.gcost;
		hcost = a.hcost;
		fcost = a.fcost;
		visited = a.visited;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const Node& node)
	{
		os << node.pos << " G:" << node.gcost << " H:" << node.hcost << " F:" << node.fcost;
		return os;
	}
};

#endif // !NODE_H_
