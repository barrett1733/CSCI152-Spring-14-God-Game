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
#include <map>
#include "obstruction-map.h"
#include "nodelist.h"
#include "nodemap.h"
#include "distance.h"

typedef std::vector<Position> PositionList;

class Pathfinding
{
	typedef Node* NodeRef;
	const double cardinalNeighbor = 1.0;
	const double intercardinalNeighbor = 1.4;
	int size_x, size_y;
	bool searchLimiter;
	
	NodeList searchList;
	NodeMap indexGraph;
	bool goalReached;
	int searchMax, searchCounter;
	NodeRef curNode, closestToGoalNode, temp;
	Position neighborPos;

	double pathCost(Direction);
	PositionList constructPath(Node*);

public:
	Pathfinding(int x, int y) : 
		size_x(x), size_y(y),
		searchLimiter(false),
		indexGraph(x, y),
		searchMax((x * y) / 8)
	{};
	PositionList findPath(Position start, Position goal, ObstructionMapReference obstructionMap);
	Position findNextPosition(Position start, Position goal, ObstructionMapReference obstructionMap);

};


#endif
