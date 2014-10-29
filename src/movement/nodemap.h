#ifndef NODEMAP_H_
#define NODEMAP_H_

#include "node.h"

class NodeMap
{
	int size;
	Node*** graph;
public:
	NodeMap(int size);
	~NodeMap();
	void clear();
	Node& operator[] (Position);
	Node& operator[] (Node*);
};


#endif