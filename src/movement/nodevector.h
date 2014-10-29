#ifndef NODEVECTOR_H_
#define NODEVECTOR_H_

#include <vector>
#include "node.h"
#include "nodemap.h"
#include "boolmap.h"

class NodeVector : public std::vector<Node*>
{
	BoolMap existsGrid;

public:
	NodeVector(int size);
	~NodeVector();
	void setup(int size);
	bool exists(Node*);
	bool exists(Position);
	void push(Node*);
	Node* pop();
	Node* find(Position);
	NodeVector::iterator find(Node*);
	void destroy(Node*);
};

#endif