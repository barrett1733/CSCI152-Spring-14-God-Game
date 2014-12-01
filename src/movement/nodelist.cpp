#include "nodelist.h"

NodeList::NodeList() :head(NULL), tail(NULL), cur(NULL), lowest(0), size(0)
{}

NodeList::~NodeList()
{
	clear();
}

bool NodeList::empty()
{
	return (size == 0);
}

bool NodeList::exists(Node* n)
{
	return (find(n) == NULL) ? false : true;
}

bool NodeList::exists(Position pos)
{
	return (find(pos) == NULL) ? false : true;
}

Node* NodeList::find(Position pos)
{
	if (!empty())
	{
		cur = head;
		while (cur != tail->next)
		{
			if (pos == cur->data->pos)
				return cur->data;
			cur = cur->next;
		}
	}
	return NULL;
}

Node* NodeList::find(Node* n)
{
	if (!empty())
	{
		cur = head;
		while (cur != tail->next)
		{
			if (*n == *cur->data)
				return cur->data;
			cur = cur->next;
		}
	}
	return NULL;
}

void NodeList::push(Node* newNode)
{
	size++;
	cur = new Element(NULL, newNode, head);
	if (head != NULL)
		head->prev = cur;
	head = cur;
	if (size == 1)
		tail = head;
}

Node* NodeList::pop()
{
	// Find lowest
	findLowest();

	// Remove lowest from list
	Node* n = lowest->data;
	remove(lowest);

	size--;
	return  n;
}

void NodeList::findLowest()
{
	lowest = head;
	cur = head;
	while (cur != NULL)
	{
		if (cur->data->fcost < lowest->data->fcost)
			lowest = cur;
		cur = cur->next;
	}
}

void NodeList::remove(Element* e)
{
	if (e->prev == NULL)
		head = e->next;
	else
		e->prev->next = e->next;

	if (e->next == NULL)
		tail = e->prev;
	else
		e->next->prev = e->prev;

	clear(e);
}

void NodeList::clear(Element* e)
{
	if (e != NULL)
	{
		e->next = e->prev = NULL;
		e->data = NULL;
	}

	delete e;
	e = NULL;
}

void NodeList::clear()
{
	cur = head;
	while (cur != NULL)
	{
		remove(cur);
		cur = head;
		size--;
	}
	head = tail = cur = lowest = NULL;
}