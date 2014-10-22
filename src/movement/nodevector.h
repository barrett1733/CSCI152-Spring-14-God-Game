#ifndef NODEVECTOR_H_
#define NODEVECTOR_H_

#include <vector>
#include "node.h"

class NodeVector : public std::vector<Node*>
{
	typedef std::vector<std::vector<bool>> VectorGrid;
	VectorGrid existsGrid;

public:
	NodeVector() {};
	NodeVector(int size);
	~NodeVector() {};
	void setup(int size);
	bool exists(Node*);
	bool exists(Position);
	void push(Node*);
	Node* pop();
	Node* find(Position);
	NodeVector::iterator find(Node*);
	void destroy();
	void destroy(Node*);
};

#endif