#include "nodemap.h"

NodeMap::NodeMap(int x_size, int y_size) : x_size(x_size), y_size(y_size)
{
	graph = new Node**[x_size];
	for (int x = 0; x < x_size; x++)
	{
		graph[x] = new Node*[y_size];
		for (int y = 0; y < y_size; y++)
			graph[x][y] = NULL;
	}
}

NodeMap::~NodeMap()
{
	for (int x = 0; x < x_size; x++)
	{
		for (int y = 0; y < y_size; y++)
		{
			delete graph[x][y];
			graph[x][y] = NULL;
		}
		delete[] graph[x];
		graph[x] = NULL;
	}
	delete[] graph;
	graph = NULL;
}

void NodeMap::clear()
{
	for (int x = 0; x < x_size; x++)
	for (int y = 0; y < y_size; y++)
	{
		delete graph[x][y];
		graph[x][y] = NULL;
	}
}

void NodeMap::assign(Node* node)
{
	graph[node->pos.getX()][node->pos.getY()] = node;
}

Node& NodeMap::operator[] (Position pos)
{
	return *graph[pos.getX()][pos.getY()];
}

Node& NodeMap::operator[] (Node* node)
{
	return *graph[node->pos.getX()][node->pos.getY()];
}
