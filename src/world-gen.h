//
//  File: world-gen.h
//  Author: Robert Boettcher
//  CSci 152
//  Spring 2014
//
//
#ifndef WORLD_GEN_H_
#define WORLD_GEN_H_

#include <vector>
#include "config.h"
#include "entity.h"

/*
WorldGeneration will initialize a two dimentional vector and fill every spot with the int that signifies open space,
then it will place all entities on the map.

Each index of the inner vector will contain an int. The location on the map will be an (x,y) coordinate system,
the x-coord will be the index of the inner vector and the y-coord the index of the outer vector

like this -->>  world_positions[outer][inner]

with 0 being the top(north) row and the higher number the bottom (south). The map will be a square with each outer 
index holding a vector the same size as the outer vector. Each different placeable item will have a differnt int 
specification designated in the entity enumeration.

each faction will start with 15 villagers and 5 cows(adjustable in "res/world-info.cfg". deer, wolves and ogres 
will be placed randomly around the map, thier numbers can be reduced by making the difference between each ones
xxxx_min and xxxx_max smaller and their xxxx_chance_to_delete larger, likewise, their numbers can be increased by 
making the difference between their xxxx_min and xxxx_max larger and reducing their xxxx_chance_to_delete in
"res/world-info.cfg".

the town center and shrine will be a buildings of larger dimension than 1x1, the locations they are placed will
be the top-left corner of the building. 2 will be placed, one for each faction.

config file in place, will have to change setProperty if other creatures are added
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

class WorldGeneration : public Config
{
public:
	WorldGeneration(int);
	~WorldGeneration();

	void PlaceResource(int, int, EntityType);
	void PlaceWildBeasts(int, int, int, EntityType);
	void PlaceTownCenter();
	void PlaceTemple();
	void PlaceAroundTC(EntityType, int, Position);
	void PrintMap();
	void nextPosition();
	void shiftFromEdge(Position&);
	void clearArea(Position);
	void createPath(int);
	void placePaths();
	void placePaths2(Position);

	int getWorldSize();
	int getEntityCount();
	int findOffset(int);
	int shiftFromEdge(int);
	int pathChange(int);

	Entity getNextEntity();

	Position findPathStart(int);
	Position getTC1();
	Position getTC2();


	std::vector< std::vector<EntityType> > world_positions;
	std::vector<int> world_info;

	bool setProperty(std::string property, int value);
private:
	int entityCount;
	Position current;
	Position TC1;
	Position TC2;
	bool cycled;
	int	TREES_MIN, TREES_MAX,
		IRON_MIN, IRON_MAX,
		STONE_MIN, STONE_MAX,
		DEER_MIN, DEER_MAX, DEER_CTD,
		WOLVES_MIN, WOLVES_MAX, WOLVES_CTD,
		OGRES_MIN, OGRES_MAX, OGRES_CTD;

};

#endif
