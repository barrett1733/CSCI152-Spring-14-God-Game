#include "world_gen.h"
#include "position.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

/*
open space: 1
trees: 2
iron: 3
beasts: 4-8 (cow-4, villager-5, deer-6, wolf-7, ogre-8)
town center: 9 
shrine: 10
*/

WorldGeneration::WorldGeneration()
{
/*************************************************
        get world info from text file
*************************************************/
	
	vector<int> *world_info=new vector<int>;
	void read_from_file();
	{
		ifstream file("worldInfo.txt");
		int n;
		while( file >> n ) world_info->push_back(n) ;
	}
	
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
	int mapsize=0;//the number is the index of the variable name, aka the line number in the text file
	int difficulty=1;
	int villagers=2;
	int cows=3;
	//vector<int>& world_info = *world_info;
	int mapEdgeLength=(*world_info)[mapsize];
	
	vector<vector<int> > *world_positions=new vector<vector<int> >;
	world_positions->resize(mapsize);
	
}

void WorldGeneration::PlaceEmptySpace(vector<vector<int> > & world_positions)
{
	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
			world_positions[outerIndex].push_back(1);
	}
}

void WorldGeneration::PlaceTrees(vector<vector<int> > & world_positions)
{

}





