#pragma once
#include "node.h"
#include "nodelist.h"
#include "nodemap.h"
#include "obstruction-map.h"
#include "distance.h"
#include <vector>

typedef std::vector<Position> Path;

class PathSearching
{
	typedef Node* NodeRef;
	int size_x, size_y;

	NodeList  openList, closedList;
	NodeMap indexGraph;
	bool goalReached;
	NodeRef current;

	void clearContents();
	Path constructPath(Node*);
	Node* searchAStar(Position start, Position goal, ObstructionMap* obsMap);
	Node* searchDijkstra(Position start, Position goal, ObstructionMap* obsMap);
	Node* searchFloydWarshall(Position start, Position goal, ObstructionMap* obsMap);

public:
	PathSearching(int x, int y) :	size_x(x), size_y(y), indexGraph(x, y) {};

	enum Algorithm { AStar, Dijkstra, FloydWarshall };

	Path findPath(Algorithm, Position start, Position goal, ObstructionMap* obsMap);
	Position findPosition(Algorithm, Position start, Position goal, ObstructionMap* obsMap);
};

