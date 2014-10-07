#include "nodelist.h"

bool NodeList::exists(Node* node)
{
	if (find(&NodeList::equalNode, node) != NULL)
		return true;
	else
		return false;
}

bool NodeList::remove(Node* a)
{
	if (!nodelist.empty())
	{
		int i = 0;
		while (i < nodelist.size())
		{
			if (*a == *nodelist[i])
				nodelist.erase(nodelist.begin() + i);
			i++;
		}
		return true;
	}
	return false;
}

Node* NodeList::compareNodes(compareNodeFn compare)
{
	if (!nodelist.empty())
	{
		Node* match = *nodelist.begin();
		for (Node* node : nodelist)
		if ((this->*compare)(match, node))
			match = node;
		return match;
	}
	return NULL;
}

Node* NodeList::find(compareNodeFn compare, Node* a)
{
	if (!nodelist.empty())
	{
		Node* match = *nodelist.begin();
		for (Node* node : nodelist)
		if ((this->*compare)(a, node))
			match = node;
		return match;
	}
	return NULL;
}
