#ifndef WORLD_GEN_H_
#define WORLD_GEN_H_

#include <vector>
#include "entity.h"

/*
WorldGeneration will initialize a two dimentional vector and fill every spot with the int that signifies open space.

Each index of the inner vector will contain an int. The location on the map will be an (x,y) coordinate system,
the x-coord etll be the index of the inner vector and the y-coord the index of the outer vector, with 0 being the top
(north) row and the higher number the bottom (south). The map will be a square with each outer vector holding a vector
the same size as the outer vector. Each different placeable item will have a differnt int specification designated in the
entity enumeration.

each faction will start with 15 villagers and 5 cows. deer, wolf and ogres will be placed randomly around the map.

the town center and shrine will be a buildings of larger dimension than 1x1, the locations they are placed will
be the top-left corner of the building. 2 will be placed, one for each faction.

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

//struct entities
//{
//	int
//};

class WorldGeneration
{
public:
	WorldGeneration(int);
	~WorldGeneration();

	int getWorldSize()
	{
		return world_info[WI_MAP_SIZE];
	}

	void PlaceResource(int min, int max, EntityType type);
	void PlaceWildBeasts(int min, int max, int delete_chance, EntityType type);
	void PlaceTownCenter();
	void PlaceTemple();
	void PlaceVillagers(EntityType type, Position pos);
	void PlaceDomesticBeasts(EntityType type, int number, Position pos);
	void PrintMap();
	Entity getNextEntity();
	int getEntityCount();
	void nextPosition();
	int findOffset(int);
	int shiftFromEdge(int);
	void shiftFromEdge(Position&);
	void clearArea(Position);
	void createPath(int);
	Position findPathStart(int);


	std::vector< std::vector<EntityType> > world_positions;
	std::vector<int> world_info;
private:
	int entityCount;
	Position current;
	Position TC1;
	Position TC2;
	bool cycled;

};

#endif
