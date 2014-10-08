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
}

Node* NodeList::pop()
{
	Node lowest = *this->front();
	int index = 0;
	for (int i = 0; i < this->size(); i++)
		if ((*this)[i]->fcost < lowest.fcost)
		{
			lowest = *(*this)[i];
			index = i;
		}
	this->erase(this->begin() + index);
	return &lowest;
}

Node* NodeList::findByPos(Node* a)
{
	Node* match = NULL;
	for (int i = 0; i < this->size(); i++)
		if (a->pos == (*this)[i]->pos)
			match = (*this)[i];
	return match;
}

Node* NodeList::find(compareNodeFn compare, Node* a)
{
	Node* match = NULL;
	for (int i = 0; i < this->size(); i++)
		if ((this->*compare)(a, (*this)[i]))
			match = (*this)[i];
	return match;
}
