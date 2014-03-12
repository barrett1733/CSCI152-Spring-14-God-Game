#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include "world_gen.h"

using namespace std;

/*
open space: 1
trees: 2
iron: 3
beasts: 4-8 (cow-4, villager-5, deer-6, wolf-7, ogre-8)
town center: 9 
shrine: 10
*/

WorldGeneration::~WorldGeneration(){}

WorldGeneration::WorldGeneration()
{
	world_info;
	world_positions;	
}

void WorldGeneration::SizeMap(vector<int> & world_info, vector<vector<int> > & world_positions)
{
/*************************************************
        get world info from text file
*************************************************/	
	ifstream myReadFile;
	void read_from_file();
	{
		ifstream file("Text.txt");
		int n;
		while( file >> n ) world_info.push_back(n) ;
	}
	for(int i=0; i<world_info.size(); i++)
		std::cout<<world_info[i]<<endl;
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
	int mapsize=0;//the number is the index of the variable name, aka the line number in the text file
	int difficulty=1;
	int villagers=2;
	int cows=3;

	int mapEdgeLength=world_info[mapsize];
		
	world_positions.resize(mapEdgeLength);
}

void WorldGeneration::PlaceEmptySpace(vector<vector<int> > & world_positions)
{
	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
			world_positions[outerIndex].push_back(1);
	}
}

void WorldGeneration::PrintMap(vector<int> & world_info)
{
	int mapsize=0;//the number is the index of the variable name, aka the line number in the text file
	int difficulty=1;
	int villagers=2;
	int cows=3;
	int temp_count=0;
	int sidelength=world_info[mapsize];
	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			cout<<world_positions[outerIndex][innerIndex];
			temp_count=temp_count+1;
			if(temp_count%sidelength==0)
				cout<<endl;
		}
	}
}

//void WorldGeneration::PlaceTrees(vector<vector<int> > & world_positions)
//{
//
//}





