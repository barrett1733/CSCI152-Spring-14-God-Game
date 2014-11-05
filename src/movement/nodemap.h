#ifndef NODEMAP_H_
#define NODEMAP_H_

#include "node.h"

class NodeMap
{
	struct NodeMapMemory
	{
		Node node;
		bool exists = false;
	};
	int x_size, y_size;
	NodeMapMemory** graph;
public:
	NodeMap(int x_size, int y_size);
	~NodeMap();
	void clear();
	bool exists(Position);
	void set(Position, Node*, double g, double h);
	Node& operator[] (Position);
	Node& operator[] (Node*);
};


#endif