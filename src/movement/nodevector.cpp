#include "nodevector.h"


NodeVector::NodeVector(int size) : existsGrid(size)
{
	reserve(size * size);
}

NodeVector::~NodeVector()
{
	for (int i = 0; i < size(); i++)
	{
		delete (*this)[i];
		(*this)[i] = NULL;
	}
	clear();
}

bool NodeVector::exists(Node* a)
{
	return exists(a->pos);
}

bool NodeVector::exists(Position pos)
{
	return existsGrid[pos];
}

void NodeVector::push(Node* n)
{
	//issue here
	existsGrid[n->pos] = true;
	//int endOfList = size();
	push_back(n);
	//(*this)[endOfList] = n;
}

Node* NodeVector::pop()
{
	if (this->empty())
	{
		std::cout << "Pathfinding error - Pop call on empty list" << std::endl;
		return NULL;
	}
	Node* lowest = front();
	int index = 0;
	for (int i = 0; i < size(); i++)
		if ((*this)[i]->fcost < lowest->fcost)
		{
			lowest = (*this)[i];
			index = i;
		}
	erase(begin() + index);
	existsGrid[lowest->pos] = true;
	return lowest;
}

Node* NodeVector::find(Position pos)
{
	for (int i = 0; i < size(); i++)
		if (pos == (*this)[i]->pos)
			return (*this)[i];
	return NULL;
}

NodeVector::iterator NodeVector::find(Node* a)
{
	for (int i = 0; i < size(); i++)
		if (*a == *(*this)[i])
			return begin() + i;
	return end();
}

void NodeVector::destroy(Node* n)
{
	NodeVector::iterator badNode = find(n);
	delete *(badNode);
	erase(badNode);
}