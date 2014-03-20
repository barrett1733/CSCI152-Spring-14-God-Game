#ifndef WORLD_GEN_H_
#define WORLD_GEN_H_

#include <vector>
#include "entity.h"

/*
WorldGeneration will initialize a two dimentional vector and fill every spot with the int that signifies open space. 

Each index of the inner vector will contain an int. The location on the map will be an (x,y) coordinate system, 
the x-coord will be the index of the inner vector and the y-coord the index of the outer vector, with 0 being the top
(north) row and the higher number the bottom (south). The map will be a square with each outer vector holding a vector the 
same size as the outer vector. Each different placeable item will have a differnt int specification.

each faction will start with 15 villagers and 5 cows. deer, wolf and ogres will be placed randomly around the map. 

the town center and shrine will be a buildings of larger dimension than 1x1, the locations they are placed will 
be the top-left corner of the building. 2 will be placed, one for each faction.
*/
class WorldGeneration
{
public:
	WorldGeneration();
	~WorldGeneration();
	void PlaceTrees();
	void PlaceStone();
	void PlaceIron();
	void PlaceTownCenter();
	void PlaceTemple();
	void PlaceEntities();
	void PrintMap();

private:
	vector<vector<int> > world_positions;
	vector<int> world_info;
};


#endif