#include "world_gen.h"
#include "position.h"
#include <iostream>
#include <vector>

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
	int mapEdgeLength=/*get map size from text file*/;
	std::vector<vector<int>> world_position(mapEdgeLength);
	for(int outerIndex=0; outerIndex<=world_position.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<=world_position.size(); innerIndex++)
			world_position[outerIndex][innerIndex]=1;
	}
}





