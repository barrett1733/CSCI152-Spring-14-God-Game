#include "nodelist.h"

bool NodeList::exists(Node* a)
{
	for (int i = 0; i < this->size(); i++)
	if (*a == *(*this)[i])
		return true;
	return false;
}

bool NodeList::exists(Position pos)
{
	for (int i = 0; i < this->size(); i++)
	if (pos == (*this)[i]->pos)
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
	for (int i = 0; i < this->size(); i++)
	if (pos == (*this)[i]->pos)
		return (*this)[i];
	return NULL;
}

NodeList::iterator NodeList::find(Node* a)
{
	for (int i = 0; i < this->size(); i++)
	if (*a == *(*this)[i])
		return this->begin() + i;
	return this->end();
}

void NodeList::destroy()
{
	for (int i = 0; i < this->size(); i++)
	{
		delete (*this)[i];
		(*this)[i] = NULL;
	}
	this->clear();
}

void NodeList::destroy(Node* n)
{
	NodeList::iterator badNode = this->find(n);
	delete *(badNode);
	this->erase(badNode);
}