#pragma once
#include "node.h"
#include <typeinfo>

class NodeGraph
{
	int size;
	Node*** graph;
public:
	NodeGraph();
	NodeGraph(int size);
	~NodeGraph();
	void clear();
	void destroy();
	Node* access(Position);
	void assign(Node*);
	void setup(int size);
};

