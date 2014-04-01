#include <iostream>
#include <math.h>
#include <vector>
#include <ctime>
#include "Node.h"

using namespace std;

bool operator< (const Node& a, const Node& b){

	return a.getPriority() > b.getPriority();

}

class Pathfinding{

	const int n = 60;
	const int m = 60;
	const int dir = 8;

	static int map[n][m];
	static int closed_map[n][m];
	static int open_map[n][m];
	static int dir_map[n][m];
	
	static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

public:
	
};

