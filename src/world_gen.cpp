#include "world_gen.h"
#include "position.h"
#include <iostream>
#include <vector>
#include<fstream>

/*
open space: 1
trees: 2
iron: 3
beasts: 4-8 (cow-4, villager-5, deer-6, wolf-7, ogre-8)
town center: 9 
shrine: 10
*/

void WorldGeneration()
{
/*************************************************
        get world info from text file
*************************************************/
	ifstream myReadFile;
	std::vector<int> world_info;
	void read_from_file();
	{
		std::ifstream file("worldInfo.txt");
		int n;
		while( file >> n ) world_info.push_back(n) ;
	}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
	int mapEdgeLength=world_info[0];
	std::vector<vector<int> > world_position(mapEdgeLength);
	for(int outerIndex=0; outerIndex<world_position.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_position.size(); innerIndex++)
			world_position[outerIndex].push_back(1);
	}
}





