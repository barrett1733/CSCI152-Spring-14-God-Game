#include "nodegraph.h"

NodeGraph::NodeGraph() {}

NodeGraph::NodeGraph(int size) : size(size)
{
	setup(size);
}

void NodeGraph::setup(int size_)
{
	size = size_;
	graph = new Node**[size];
	for (int i = 0; i < size; i++)
	{
		graph[i] = new Node*[size];
		for (int j = 0; j < size; j++)
			graph[i][j] = NULL;
	}
}

NodeGraph::~NodeGraph()
{
	this->destroy();
}

void NodeGraph::clear()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			delete graph[i][j];
			graph[i][j] = NULL;
		}
}

void NodeGraph::destroy()
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

Node* NodeGraph::access(Position pos)
{
	Node* temp = graph[pos.getX()][pos.getY()];
	return temp;
}

void NodeGraph::assign(Node* n)
{
	graph[n->pos.getX()][n->pos.getY()] = n;
}
