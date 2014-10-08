#ifndef NODELIST_H_
#define NODELIST_H_

#include "node.h"
#include <vector>

class NodeList : public std::vector<Node*>
{
	typedef bool(NodeList::*compareNodeFn) (Node*, Node*);
	Node* find(compareNodeFn, Node*);
	bool lessThanGcost(Node* a, Node* b) { return a->gcost < b->gcost; }
	bool equalNode(Node*a, Node* b) { return *a == *b; }
	bool equalPos(Node*a, Node* b) { return a->pos == b->pos; }

public:
	bool exists(Node*);
	void push(Node*);
	Node* pop();
	Node* findByPos(Node*);

};

#endif