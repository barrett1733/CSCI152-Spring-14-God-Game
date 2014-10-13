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


typedef std::vector<Position> PositionList;
#define cardinalNeighbor 1
#define intercardinalNeighbor 1.4

class Pathfinding
{

	NodeList searchList, indexList, closedList;
	bool goalReached;

	Direction direction(Position, Position);
	Direction* parseDirection(Direction);

	double calcHCost(Position start, Position goal);
	Position getNeighbor(Position, Direction);
	PositionList* constructPath(Node*);

	NodeList* identifySuccessors(Node* cur, Position start, Position end);
	Node* jump(Node* cur, Direction direction, Position start, Position end);

public:
	PositionList* findPath(Position start, Position goal, ObstructionMap obstructionMap);

};


#endif
