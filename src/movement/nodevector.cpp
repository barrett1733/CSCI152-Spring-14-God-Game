#include "nodevector.h"


NodeVector::NodeVector(int size)
{
	setup(size);
}

void NodeVector::setup(int size)
{
	reserve(size * size);
	existsGrid.resize(size);
	for (int i = 0; i < size; i++)
	{
		existsGrid.resize(size);
		for (int j = 0; j < size; j++)
			existsGrid[i][j] = 0;
	}
}

bool NodeVector::exists(Node* a)
{
	return exists(a->pos);
}

bool NodeVector::exists(Position pos)
{
	return existsGrid[pos.getX()][pos.getY()];
}

void NodeVector::push(Node* n)
{
	existsGrid[n->pos.getX()][n->pos.getY()] = true;
	(*this)[size()] = n;
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

void NodeVector::destroy()
{
	for (int i = 0; i < size(); i++)
	{
		delete (*this)[i];
		(*this)[i] = NULL;
	}
	clear();
}

void NodeVector::destroy(Node* n)
{
	NodeVector::iterator badNode = find(n);
	delete *(badNode);
	erase(badNode);
}