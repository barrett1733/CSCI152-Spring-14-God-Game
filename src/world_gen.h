#ifndef WORLD_GEN_H_
#define WORLD_GEN_H_

#include <vector>

#include "position.h"

using namespace std;
/*
WorldGeneration will initialize a two dimentional vector and fill every spot with the int that signifies open space(1). 

Each index of the inner vector will contain an int. The location on the map will be an (x,y) coordinate system, 
the x-coord will be the index of the outer vector and the y-coord the index of the inner vecor, with 0 being the bottom
(south) row and the higher number the top (north). The map will be a square with each outer vector holding a vector the 
same size as the outer vector. Each different placeable item will have a differnt int specification:
open space: 1
trees: 2
iron: 3
beasts: 4-8 (cow-4, villager-5, deer-6, wolf-7, ogre-8)
town center: 9 
shrine: 10

each faction will start with 15 villagers and 15 cows. deer, wolf and ogres will be placed randomly around the map. 

the town center and shrine will be a buildings of larger dimension than 1x1, the locations the 9 and 10 are placed will 
bethe top-left corner of the building. 2 will be placed, one for each faction.
*/
class WorldGeneration
{
public:
	WorldGeneration();
	~WorldGeneration();
	void PlaceTrees(/*int mapsize, */int difficulty, vector<vector<int> > & world_positions);
	void PlaceStone(/*int mapsize, */int difficulty, vector<vector<int> > & world_positions);
	void PlaceIron(/*int mapsize, */int difficulty, vector<vector<int> > & world_positions);
	void PlaceBeasts(/*int mapsize, */int difficulty, vector<vector<int> > & world_positions);
	void PlaceTownCenter(/*int mapsize, */int difficulty, vector<vector<int> > & world_positions);
	void PlaceShrine(/*int mapsize, */int difficulty, vector<vector<int> > & world_positions);

private:
	vector<vector<int> > world_positions;
}

#endif