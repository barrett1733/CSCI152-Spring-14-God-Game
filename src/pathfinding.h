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
#include <ctime>
#include "world-gen.h"
#include "Node.h"
#include "vector2.h"

using namespace std;


class Pathfinding{

	void set_Start_Goal(Node start, Node goal);
	void pathOpened(int x, int y, double newCost, Node* parent);
	Node* getNextNode();
	void continuePath();

	Node* startNode;
	Node* goalNode;

	vector<Node*> openList;
	vector<Node*> visitedList;
	vector< vector2* > pathToGoal;

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
