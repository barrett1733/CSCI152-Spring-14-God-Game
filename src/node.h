#ifndef NODE_H_
#define NODE_H_

#include "position.h"
#include <iostream>

struct Node {
	Position pos;
	Node* parentNode;
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
	friend std::ostream& operator<<(std::ostream& os, const Node& node)
	{
		os << node.pos << " | " << node.gcost << " | " << node.hcost << " | " << node.fcost;
		return os;
	}
};

#endif // !NODE_H_
