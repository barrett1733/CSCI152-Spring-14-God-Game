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
typedef std::pair<Position, double> Neighbor; // pair (position, gcost)
#define cardinalNeighbor 1
#define intercardinalNeighbor 1.4

class Pathfinding
{
	int worldSize;
	NodeList searchList;
	NodeMap indexGraph;
	bool goalReached;
	Neighbor neighborArray[8]; // Should never be anymore than 8 neighbors

	void neighbors(Position);

	double calcHCost(Position start, Position goal);
	Position getNeighbor(Position, Direction);
	PositionList constructPath(Node*);

public:
	Pathfinding(int worldSize);
	PositionList findPath(Position start, Position goal, ObstructionMapReference obstructionMap);

};


#endif
