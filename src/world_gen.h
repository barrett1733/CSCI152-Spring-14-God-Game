#ifndef WORLD_GEN_H_
#define WORLD_GEN_H_

#include <vector>

using namespace std;
/*
WorldGeneration will initialize a two dimentional vector and fill every spot with the int that signifies open space(1). 

Each index of the inner vector will contain an int. The location on the map will be an (x,y) coordinate system, 
the x-coord will be the index of the outer vector and the y-coord the index of the inner vecor, with 0 being the top
(north) row and the higher number the bottom (south). The map will be a square with each outer vector holding a vector the 
same size as the outer vector. Each different placeable item will have a differnt int specification:
open space: 1
trees: 2
iron: 3
mobile entities: 4-8 (cow-4, villager-5, deer-6, wolf-7, ogre-8)
town center: 9 
shrine: 10

each faction will start with 15 villagers and 15 cows. deer, wolf and ogres will be placed randomly around the map. 

the town center and shrine will be a buildings of larger dimension than 1x1, the locations the 9 and 10 are placed will 
be the top-left corner of the building. 2 will be placed, one for each faction.
*/
class WorldGeneration
{
public:
	WorldGeneration();
	~WorldGeneration();
	void PlaceEmptySpace(vector<vector<int> > & world_positions);
	void PlaceTrees(vector<vector<int> > & world_positions);
	void PlaceStone(vector<vector<int> > & world_positions);
	void PlaceIron(vector<vector<int> > & world_positions);
	void PlaceEntities(vector<vector<int> > & world_positions);
	void PlaceTownCenter(vector<vector<int> > & world_positions);
	void PlaceShrine(vector<vector<int> > & world_positions);

private:
	vector<vector<int> > world_positions;
	vector<int> world_info;
}


#endif