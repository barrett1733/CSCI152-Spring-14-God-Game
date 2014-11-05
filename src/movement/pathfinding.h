#ifndef PATHFINDING_H_
#define PATHFINDING_H_
/*
Jump Point Search Code:
https://code.google.com/p/ddh/

Jump Point Search Paper:
http://www.aaai.org/ocs/index.php/AAAI/AAAI11/paper/viewFile/3761/4007

Jump Point Search Explaination:
http://harablog.wordpress.com/2011/09/07/jump-point-search/

Jump Point Search Demo (Other searches included):
http://qiao.github.io/PathFinding.js/visual/

*/

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>
#include "obstruction-map.h"
#include "nodelist.h"
#include "nodemap.h"

typedef std::vector<Position> PositionList;

class Pathfinding
{
	typedef Node* NodeRef;
	const int cardinalNeighbor = 1.0;
	const int intercardinalNeighbor = 1.4;
	
	NodeList searchList;
	NodeMap indexGraph;
	bool goalReached;
	int searchMax, searchCounter;
	NodeRef startNode, curNode, closestToGoalNode, temp, newNeighbor;

	// Should never be anymore than 8 neighbors
	Position neighborArray[8]; 

	void populateNeighbors(Position);
	Position neighbor(Position, int index);

	double manhattanDistance(Position start, Position goal);
	double euclideanDistance(Position start, Position goal);
	Position generateNeighbor(Position, int);
	Position getNeighbor(Position, Direction);
	PositionList constructPath(Node*);

public:
	Pathfinding() : 
		indexGraph(Position::max_x + 1, Position::max_y + 1),
		searchMax((Position::max_x + 1 + Position::max_y + 1) / 8)
	{};
	PositionList findPath(Position start, Position goal, ObstructionMapReference obstructionMap);
	Position findNextPosition(Position start, Position goal, ObstructionMapReference obstructionMap);

};


#endif
