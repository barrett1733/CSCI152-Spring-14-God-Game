#ifndef NODEVECTOR_H_
#define NODEVECTOR_H_

#include <vector>
#include "node.h"

class NodeVector : std::vector<Node*>
{

public:
	NodeVector();
	~NodeVector();
	/*
	bool empty();
	bool exists(Node*);
	bool exists(Position);
	Node* find(Node*);
	Node* find(Position);
	void clear();*/
};

#endif