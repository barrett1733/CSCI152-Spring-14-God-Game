#ifndef NODELIST_H_
#define NODELIST_H_

#include "node.h"

// First in, lowest F value out

/////////////////////////////////////////////////////
// Interesting things to note and try
// 
// Vectors are slightly slower than arrays when used 
// correctly. push_back is guranteed to be slower.
// Reserving memory space before hand and using
// using subscript ([]) operator speed up access
// greatly.
// 
//	- SB - 10.18.2014
/////////////////////////////////////////////////////

class NodeList
{
	struct Element
	{
		Node* data;
		Element *next, *prev;
		Element() : next(NULL), data(NULL), prev(NULL)
		{}
		Element(Element* prev, Node* data, Element* next) :
			next(next), data(data), prev(prev)
		{}
		Element& operator= (Element& a)
		{
			next = a.next;
			prev = a.prev;
			data = a.data;
			return *this;
		}
	};
	// Head points to the first element
	// Tail points to the last element
	Element *head, *tail, *cur, *lowest;
	int size;
	void remove(Element*);
	void clear(Element*);
	Element* find(Element*);
	void findLowest();

public:
	NodeList();
	~NodeList();
	bool empty();
	bool exists(Node*);
	bool exists(Position);
	Node* find(Node*);
	Node* find(Position);
	void push(Node*);
	Node* pop();
	void clear();
};

#endif