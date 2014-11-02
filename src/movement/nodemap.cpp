#include "nodemap.h"

NodeMap::NodeMap(int x_size, int y_size) : x_size(x_size), y_size(y_size)
{
	graph = new Node**[y_size];
	for (int y = 0; y < y_size; y++)
	{
		graph[y] = new Node*[x_size];
		for (int x = 0; x < x_size; x++)
			graph[y][x] = NULL;
	}
}

NodeMap::~NodeMap()
{
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			delete graph[y][x];
			graph[y][x] = NULL;
		}
		delete[] graph[y];
		graph[y] = NULL;
	}
	delete[] graph;
	graph = NULL;
}

void NodeMap::clear()
{
	for (int y = 0; y < y_size; y++)
	for (int x = 0; x < x_size; x++)
	{
		delete graph[y][x];
		graph[y][x] = NULL;
	}
}

void NodeMap::assign(Node* node)
{
	graph[node->pos.getY()][node->pos.getX()] = node;
}

Node& NodeMap::operator[] (Position pos)
{
	return *graph[pos.getY()][pos.getX()];
}

Node& NodeMap::operator[] (Node* node)
{
	return *graph[node->pos.getY()][node->pos.getX()];
}
