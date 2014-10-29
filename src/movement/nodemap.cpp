#include "nodemap.h"

NodeMap::NodeMap(int size) : size(size)
{
	graph = new Node**[size];
	for (int i = 0; i < size; i++)
	{
		graph[i] = new Node*[size];
		for (int j = 0; j < size; j++)
			graph[i][j] = NULL;
	}
}

NodeMap::~NodeMap()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			delete graph[i][j];
			graph[i][j] = NULL;
		}
		delete[] graph[i];
		graph[i] = NULL;
	}
	delete[] graph;
	graph = NULL;
}

void NodeMap::clear()
{
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	{
		delete graph[i][j];
		graph[i][j] = NULL;
	}
}

Node& NodeMap::operator[] (Position pos)
{
	return *graph[pos.getX()][pos.getY()];
}

Node& NodeMap::operator[] (Node* node)
{
	return *graph[node->pos.getX()][node->pos.getY()];
}
