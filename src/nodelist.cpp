#include "nodelist.h"

bool NodeList::exists(Node* a)
{
	for (Node* node : *this)
		if (a->pos == node->pos)
			return true;
	return false;
}

Node* NodeList::pop()
{
	Node* lowest = this->front();
	int index = 0;
	for (int i = 0; i < this->size(); i++)
		if ((*this)[i]->fcost < lowest->fcost)
		{
			lowest = (*this)[i];
			index = i;
		}
	this->erase(this->begin() + index);
	return lowest;
}

Node* NodeList::findByPos(Node* a)
{
	Node* match = NULL;
	for (int i = 0; i < this->size(); i++)
		if (a->pos == (*this)[i]->pos)
			match = (*this)[i];
	return match;
}

// Returns a pointer to the matching Node in the list
Node* NodeList::find(Node* a)
{
	Node* match = NULL;
	for (int i = 0; i < this->size(); i++)
		if (a == (*this)[i])
			match = (*this)[i];
	return match;
}
