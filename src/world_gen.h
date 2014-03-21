#ifndef WORLD_GEN_H_
#define WORLD_GEN_H_

#include <vector>
#include "entity.h"

/*
WorldGeneration will initialize a two dimentional vector and fill every spot with the int that signifies open space. 

Each index of the inner vector will contain an int. The location on the map will be an (x,y) coordinate system, 
the x-coord will be the index of the inner vector and the y-coord the index of the outer vector, with 0 being the top
(north) row and the higher number the bottom (south). The map will be a square with each outer vector holding a vector 
the same size as the outer vector. Each different placeable item will have a differnt int specification designated in the 
entity enumeration.

each faction will start with 15 villagers and 5 cows. deer, wolf and ogres will be placed randomly around the map. 

the town center and shrine will be a buildings of larger dimension than 1x1, the locations they are placed will 
be the top-left corner of the building. 2 will be placed, one for each faction.
*/
class WorldGeneration
{
public:
	WorldGeneration();
	~WorldGeneration();
	void PlaceResource(int min, int max, int type);
	void PlaceWildBeasts(int min, int max, int delete_chance, int type);
	void PlaceTownCenter();
	void PlaceTemple();
	void PlaceVillagersAndCows();
	void PrintMap();

//private:
	std::vector< std::vector<int> > world_positions;
	std::vector<int> world_info;
	int TC1_x_coord_topleft;
	int TC1_y_coord_topleft;
	int TC2_x_coord_topleft;
	int TC2_y_coord_topleft;
};

enum WorldInfo 
{
	ET_MAP_SIZE = 0x00,
	ET_DIFFICULTY = 0x01,
	ET_NUM_OF_VILLAGERS = 0x02,
	ET_NUM_OF_COWS = 0x03
};
#endif