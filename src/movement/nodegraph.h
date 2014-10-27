#ifndef NODEGRAPH_H_
#define NODEGRAPH_H_

#include "node.h"

class NodeGraph
{
	int size;
	Node*** graph;
public:
	NodeGraph() {};
	NodeGraph(int size);
	~NodeGraph();
	void setup(int size);
	void clear();
	void destroy();
	Node& operator[] (Position);
	Node* access(Position);
	void assign(Node*);
};


#endif