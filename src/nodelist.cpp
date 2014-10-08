#include "nodelist.h"

bool NodeList::exists(Node* a)
{
	for (Node* node : *this)
		if (*a == *node)
			return true;
	return false;
}

void NodeList::push(Node* a)
{
	this->push_back(a);
	std::sort(this->begin(), this->end(), lessThanGcost);
}

Node* NodeList::pop()
{
	Node a = *this->front();
	this->erase(this->begin());
	return &a;
}

Node* NodeList::findByPos(Node* a)
{
	return find(equalPos, a);
}

Node* NodeList::find(compareNodeFn compare, Node* a)
{
	Node* match = NULL;
	for (int i = 0; i < this->size(); i++)
		if ((this->*compare)(a, (*this)[i]))
			match = (*this)[i];
	return match;
}
