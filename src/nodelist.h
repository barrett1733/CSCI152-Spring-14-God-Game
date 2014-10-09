#ifndef NODELIST_H_
#define NODELIST_H_

#include "node.h"
#include <vector>

class NodeList : public std::vector<Node*>
{
	typedef bool(NodeList::*compareNodeFn) (Node*, Node*);
	bool lessThanGcost(Node* a, Node* b) { return a->gcost < b->gcost; }
	bool equalNode(Node*a, Node* b) { return *a == *b; }
	bool equalPos(Node*a, Node* b) { return a->pos == b->pos; }

public:
	bool exists(Node*);
	Node* pop();
	Node* findByPos(Node*);
	Node* find(Node*);
	friend std::ostream& operator<<(std::ostream& os, const NodeList& list)
	{
		for (Node* a : list)
			os << "- " << *a << std::endl;
		return os;
	}

};

#endif