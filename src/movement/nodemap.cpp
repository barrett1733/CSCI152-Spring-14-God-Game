#include "nodemap.h"

NodeMap::NodeMap(int x_size, int y_size) : x_size(x_size), y_size(y_size)
{
	graph = new NodeMapMemory*[y_size];
	for (int y = 0; y < y_size; y++)
		graph[y] = new NodeMapMemory[x_size];
}

NodeMap::~NodeMap()
{
	for (int y = 0; y < y_size; y++)
	{
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
		graph[y][x].exists = false;
	}
}

bool NodeMap::exists(Position pos)
{
	return graph[pos.getY()][pos.getX()].exists;
}

void NodeMap::set(Position pos, Node* par, double g, double h)
{
	int x = pos.getX();
	int y = pos.getY();
	if (!graph[y][x].exists)
	{
		graph[y][x].exists = true;
		graph[y][x].node.pos = pos;
		graph[y][x].node.parentNode = par;
		graph[y][x].node.gcost = g;
		graph[y][x].node.hcost = h;
		graph[y][x].node.fcost = g + h;
	}
}

Node& NodeMap::operator[] (Position pos)
{
	return graph[pos.getY()][pos.getX()].node;
}

Node& NodeMap::operator[] (Node* node)
{
	return graph[node->pos.getY()][node->pos.getX()].node;
}
