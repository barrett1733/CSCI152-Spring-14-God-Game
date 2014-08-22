//
//  File: pathfinding.h
//  Author: Anthony Smith
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
#ifndef PATHFINDING_H_
#define PATHFINDING_H_


#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include "obstruction-map.h"

struct Node {
	Position pos;
	Node* parentNode;
	double exactCost, heuristicCost, finalCost;
	Node(Position pos, Node* parent, double hCost) :
		pos(pos), 
		parentNode(parent),
		exactCost(0),
		heuristicCost(hCost),
		finalCost(0)
	{}
};

typedef std::vector<Node*> NodeList;
typedef std::vector<Node*>* NodeListRef;
typedef std::vector<Node*>::iterator NodeListIter;
typedef std::vector<Node*>::iterator* NodeListIterRef;

bool exists(NodeListRef nodeList, Node* node)
{
	for (int i = 0; i < nodeList->size(); i++)
	{
		if (nodeList->at(i) == node)
		{
			return true;
		}
	}
	return false;
}

Node* findLowestFCostNode(NodeListRef nodeList)
{
	if (!nodeList->empty())
	{
		Node* lowestNode = nodeList->at(0);
		for (int i = 0; i < nodeList->size(); i++)
			if (nodeList->at(i)->finalCost < lowestNode->finalCost)
				lowestNode = nodeList->at(i);
		return lowestNode;
	}
	return NULL;
}

NodeListRef findPath(Position start, Position goal, ObstructionMap obstructionMap)
{
	NodeList openList;
	NodeList closedList;
	double heuristicCost = sqrt(pow((start.getX() - goal.getX()), 2) + pow((start.getY() - goal.getY()), 2));
	bool goalReached = false;

	Node startNode(start, NULL, heuristicCost);
	openList.push_back(&startNode);

	Node* currentNode = NULL;

	while (!goalReached)
	{
		currentNode = findLowestFCostNode(&openList);
		if (currentNode == NULL)
		{
			std::cout << "Path finding error" << std::endl;
			break;
		}
		else
		{
			if (currentNode->pos == goal)
				goalReached = true;
			else
			{
				closedList.push_back(currentNode);
				openList.erase(std::find(openList.begin(), openList.end(), currentNode));
			
				//find Neighbors
				for (int x = -1; x <= 1; x++)
				for (int y = -1; y <= 1; y++)
				{
					Node neighborNode(Position(currentNode->pos.getX() + x, currentNode->pos.getY() + y), currentNode, heuristicCost);
					if (!exists(&closedList, &neighborNode))
					{
						neighborNode.parentNode = currentNode;
						neighborNode.exactCost++;
						neighborNode.finalCost = neighborNode.exactCost + neighborNode.heuristicCost;
					}
				}
			}
		}
	}
}
/*
1. Find node closest to your position and declare it start node and put it on
the open list.
2. While there are nodes in the open list:
	3. Pick the node from the open list having the smallest F score. Put it on
	the closed list (you don't want to consider it again).
	4. For each neighbor (adjacent cell) which isn't in the closed list:
		5. Set its parent to current node.
		6. Calculate G score (distance from starting node to this neighbor) and
		add it to the open list
		7. Calculate F score by adding heuristics to the G value.
*/
// A*
/*
create the open list of nodes, initially containing only our starting node
create the closed list of nodes, initially empty
while (we have not reached our goal) {
consider the best node in the open list (the node with the lowest f value)
	if (this node is the goal) {
		then we're done
	}
	else {
		move the current node to the closed list and consider all of its neighbors
		for (each neighbor) {
			if (this neighbor is in the closed list and our current g value is lower) {
				update the neighbor with the new, lower, g value
				change the neighbor's parent to our current node
			}
			else if (this neighbor is in the open list and our current g value is lower) {
				update the neighbor with the new, lower, g value
				change the neighbor's parent to our current node
			}
			else this neighbor is not in either the open or closed list {
				add the neighbor to the open list and set its g value
			}
		}
	}
}

*/
class Pathfinding{

	void set_Start_Goal(Node start, Node goal);
	void pathOpened(int x, int y, double newCost, Node* parent);
	void continuePath();


	Node* startNode;
	Node* goalNode;

	std::vector<Node*> openList;
	std::vector<Node*> visitedList;
	std::vector< vector2* > pathToGoal;

	public:
		Pathfinding(void);

		void findPath(vector2 currentPos, vector2 targetPos);
		vector2 nextPathPos();
		void clearOpenList() { openList.clear(); }
		void clearVisitedList() { visitedList.clear(); }
		void clearPathToGoal() { pathToGoal.clear(); }
		void Store_Paths(vector< vector2* > path);
		bool initializedStartGoal;
		bool foundGoal;
	
};

#endif
