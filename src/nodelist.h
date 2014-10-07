#ifndef NODELIST_H_
#define NODELIST_H_

#include "node.h"
#include <vector>

class NodeList
{
	std::vector<Node*> nodelist;
	typedef bool(NodeList::*compareNodeFn) (Node*, Node*);

public:
	bool exists(Node*);
	bool remove(Node*);
	Node* compareNodes(compareNodeFn);
	Node* find(compareNodeFn, Node*);
	void push(Node*);
	Node* pop();

	bool lessThanGcost(Node* a, Node* b) { return a->gcost < b->gcost; }
	bool equalNode(Node*a, Node* b) { return *a == *b; }
	bool equalPos(Node*a, Node* b) { return a->pos == b->pos; }

};

#endif