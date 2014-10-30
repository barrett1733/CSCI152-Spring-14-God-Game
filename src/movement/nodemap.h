#ifndef NODEMAP_H_
#define NODEMAP_H_

#include "node.h"

class NodeMap
{
	int x_size, y_size;
	Node*** graph;
public:
	NodeMap(int x_size, int y_size);
	~NodeMap();
	void clear();
	void assign(Node*);
	Node& operator[] (Position);
	Node& operator[] (Node*);
};


#endif