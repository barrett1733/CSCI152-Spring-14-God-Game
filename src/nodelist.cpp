#include "nodelist.h"

bool NodeList::exists(Node* a)
{
	for (Node* node : *this)
	if (*a == *node)
		return true;
	return false;
}

bool NodeList::exists(Position pos)
{
	for (Node* node : *this)
	if (pos == node->pos)
		return true;
	return false;
}

Node* NodeList::pop()
{
	if (this->empty())
	{
		std::cout << "Pathfinding error - Pop call on empty list" << std::endl;
		return NULL;
	}
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

Node* NodeList::find(Position pos)
{
	for (NodeList::iterator match = this->begin(); match != this->end(); ++match)
	if (pos == (*match)->pos)
		return *match;
	return NULL;
}

NodeList::iterator NodeList::find(Node* a)
{
	for (NodeList::iterator match = this->begin(); match != this->end(); ++match)
	if (*a == **match)
		return match;
	return this->end();
}

void NodeList::destroy()
{
	for (Node* n : *this)
	{
		delete n;
		n = NULL;
	}
	this->clear();
}

void NodeList::destroy(Node* n)
{
	NodeList::iterator badNode = this->find(n);
	delete *(badNode);
	this->erase(badNode);
}