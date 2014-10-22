#ifndef POINTERGRAPH_H_
#define POINTERGRAPH_H_

template <class Type>
class PointerGraph
{
	int size;
	Type*** graph;
public:
	PointerGraph() {};
	PointerGraph(int size);
	~PointerGraph();
	void setup(int size);
	void clear();
	void destroy();
	Type& operator[] (Position);
	Type* access(Position);
	void assign(Type*);
};

template <class Type>
PointerGraph<Type>::PointerGraph(int size) : size(size)
{
	setup(size);
}

template <class Type>
PointerGraph<Type>::~PointerGraph()
{
	this->destroy();
}

template <class Type>
void PointerGraph<Type>::setup(int size_)
{
	size = size_;
	graph = new Type**[size];
	for (int i = 0; i < size; i++)
	{
		graph[i] = new Type*[size];
		for (int j = 0; j < size; j++)
			graph[i][j] = NULL;
	}
}

template <class Type>
void PointerGraph<Type>::clear()
{
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	{
		delete graph[i][j];
		graph[i][j] = NULL;
	}
}

template <class Type>
void PointerGraph<Type>::destroy()
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

template <class Type>
Type& PointerGraph<Type>::operator[] (Position pos)
{
	return graph[pos.getX()][pos.getY()];
}

template <class Type>
Type* PointerGraph<Type>::access(Position pos)
{
	Type* temp = graph[pos.getX()][pos.getY()];
	return temp;
}

template <class Type>
void PointerGraph<Type>::assign(Type* n)
{
	graph[n->pos.getX()][n->pos.getY()] = n;
}

#endif