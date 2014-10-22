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
#include "nodevector.h"
#include "pointergraph.h"

typedef std::vector<Position> PositionList;
#define cardinalNeighbor 1
#define intercardinalNeighbor 1.4

#define vector true

class Pathfinding
{
	NodeVector searchVector;
	NodeList searchList, indexList;
	PointerGraph<Node> indexGraph;
	bool goalReached;

	typedef std::pair<Position, double> neighborTuple;
	neighborTuple neighborPos[8]; // Should never be anymore than 8 neighbors

	double calcHCost(Position start, Position goal);
	PositionList constructPath(Node*);

public:
	Pathfinding();
	PositionList findPath(Position start, Position goal, ObstructionMapReference obstructionMap);

};


#endif
