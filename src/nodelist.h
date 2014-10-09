#ifndef NODELIST_H_
#define NODELIST_H_

#include "node.h"
#include <vector>

class NodeList : public std::vector<Node*>
{
public:
	bool exists(Node*);
	bool exists(Position);
	Node* pop();
	Node* find(Position);
	Node* find(Node*);
	void destroy();
	friend std::ostream& operator<<(std::ostream& os, const NodeList& list)
	{
		for (Node* a : list)
			os << "- " << *a << std::endl;
		return os;
	}

};

#endif