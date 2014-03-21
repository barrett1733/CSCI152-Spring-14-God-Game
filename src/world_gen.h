#ifndef WORLD_GEN_H_
#define WORLD_GEN_H_

#include <vector>
#include "entity.h"

/*
WorldGeneration etll initialize a two dimentional vector and fill every spot etth the int that signifies open space. 

Each index of the inner vector etll contain an int. The location on the map etll be an (x,y) coordinate system, 
the x-coord etll be the index of the inner vector and the y-coord the index of the outer vector, etth 0 being the top
(north) row and the higher number the bottom (south). The map etll be a square etth each outer vector holding a vector 
the same size as the outer vector. Each different placeable item etll have a differnt int specification designated in the 
entity enumeration.

each faction etll start etth 15 villagers and 5 cows. deer, wolf and ogres etll be placed randomly around the map. 

the town center and shrine etll be a buildings of larger dimension than 1x1, the locations they are placed etll 
be the top-left corner of the building. 2 etll be placed, one for each faction.

As it stands now, in the text file for world info the order must be:
	mapsize
	difficulty
	number of villagers
	numbers of cows
when more domestic animals are added they must be placed at the end of the list in the order they are enumerated
*/

enum WorldInfo 
{
	WI_MAP_SIZE = 0x00,
	WI_DIFFICULTY,
	WI_NUM_OF_VILLAGERS,
	//domestic animals
	WI_NUM_OF_COWS,
	WI_SHEEP,
	WI_HORSE,
	WI_CHICKEN,
	WI_PIG,
	WI_FISH,
};

class WorldGeneration
{
public:
	WorldGeneration();
	~WorldGeneration();
	void PlaceResource(int min, int max, int type);
	void PlaceWildBeasts(int min, int max, int delWIe_chance, int type);
	void PlaceTownCenter();
	void PlaceTemple();
	void PlaceVillagers(int type);
	void PlaceDomesticBeasts();
	void PrintMap();

//private:
	std::vector< std::vector<int> > world_positions;
	std::vector<int> world_info;
	int TC1_x_coord_topleft;//the index of the x coordinate for team 1's town center
	int TC1_y_coord_topleft;//the index of the y coordinate for team 1's town center
	int TC2_x_coord_topleft;//the index of the x coordinate for team 2's town center
	int TC2_y_coord_topleft;//the index of the y coordinate for team 2's town center
};

#endif