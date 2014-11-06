#include "nodemap.h"

NodeMap::NodeMap(int x_size, int y_size) : 
	x_size(x_size), 
	y_size(y_size)
{
	graph = new Node*[y_size];
	existsGraph = new bool*[y_size];
	for (int y = 0; y < y_size; y++)
	{
		graph[y] = new Node[x_size];
		existsGraph[y] = new bool[x_size];
		for (int x = 0; x < x_size; x++)
			existsGraph[y][x] = false;
	}
}

NodeMap::~NodeMap()
{
	for (int y = 0; y < y_size; y++)
	{
		delete[] graph[y];
		delete[] existsGraph[y];
		graph[y] = NULL;
		existsGraph[y] = NULL;
	}
	delete[] graph;
	delete[] existsGraph;
	graph = NULL;
	existsGraph = NULL;
}

void NodeMap::clear()
{
	for (int y = 0; y < y_size; y++)
	for (int x = 0; x < x_size; x++)
	{
		existsGraph[y][x] = false;
	}
}

bool NodeMap::exists(Position pos)
{
	return existsGraph[pos.getY()][pos.getX()];
}

void NodeMap::set(Position pos, Node* par, double g, double h)
{
	int x = pos.getX();
	int y = pos.getY();
	if (!existsGraph[y][x])
	{
		existsGraph[y][x] = true;
		graph[y][x].pos = pos;
		graph[y][x].parentNode = par;
		graph[y][x].gcost = g;
		graph[y][x].hcost = h;
		graph[y][x].fcost = g + h;
	}
}

Node& NodeMap::operator[] (Position pos)
{
	return graph[pos.getY()][pos.getX()];
}

Node& NodeMap::operator[] (Node* node)
{
	return graph[node->pos.getY()][node->pos.getX()];
}
