#ifndef NODE_H_
#define NODE_H_

#include "position.h"
#include <iostream>

struct Node {
	Position pos;
	Node* parentNode;
	bool visited = false;
	double gcost, fcost;
	Node() :
		pos(Position(0, 0)),
		parentNode(NULL),
		gcost(0),
		fcost(0)
	{}
	Node(Position pos, Node* parent, double g, double f) :
		pos(pos),
		parentNode(parent),
		gcost(g),
		fcost(f)
	{}
	void set(Position pos_, Node* par, double g, double f)
	{
		pos = pos_;
		parentNode = par;
		gcost = g;
		fcost = f;
	}
	bool operator== (Node &a) const
	{
		return (pos == a.pos &&
			parentNode == a.parentNode &&
			gcost == a.gcost &&
			fcost == a.fcost &&
			visited == a.visited);
	}
	Node& operator= (Node& a)
	{
		pos = a.pos;
		parentNode = a.parentNode;
		gcost = a.gcost;
		fcost = a.fcost;
		visited = a.visited;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const Node& node)
	{
		if (node.parentNode != NULL)
			os << node.pos << " " << node.parentNode->pos << " G:" << node.gcost << " F:" << node.fcost;
		else
			os << node.pos << " (N,N)" << " G:" << node.gcost << " F:" << node.fcost;
		return os;
	}
};

#endif // !NODE_H_
