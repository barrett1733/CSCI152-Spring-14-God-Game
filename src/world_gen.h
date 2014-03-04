#ifndef WORLD_GEN_H_
#define WORLD_GEN_H_

#include <vector>
#include "position.h"

class WorldGeneration
{
public:
	void PlaceTrees(int mapsize, int difficulty, vector<vector<int> > & world)
	void PlaceStone(int mapsize, int difficulty, vector<vector<int> > & world)
	void PlaceIron(int mapsize, int difficulty, vector<vector<int> > & world)
	void PlaceBeasts(int mapsize, int difficulty, vector<vector<int> > & world)

private:
	vector<vector<int> > world_positions;
}

#endif