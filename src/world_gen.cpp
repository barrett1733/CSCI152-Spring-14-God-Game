#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>
#include <cmath>
#include <string>
#include "world_gen.h"

using namespace std;

WorldGeneration::~WorldGeneration(){}

WorldGeneration::WorldGeneration()
{
	// If rand() were not seeded anywhere else in the program, you *could* seed it here:
	// srand(time(0));
	// and absolutely no where else, but it should be seeded somewhere else.
	time_t timer;
	srand(time(&timer));//rand must be seeded before placement, if not here then in another module that needs it first
	//if it is used I will remove it from this location

	world_info;
	world_positions;
	TC1_x_coord_topleft;
	TC1_y_coord_topleft;
	TC2_x_coord_topleft;
	TC2_y_coord_topleft;

	/*****************
	***get map info***
	*****************/

	ifstream myReadFile;
	void read_from_file();
	{
		ifstream file("worldInfo.txt");
		int n;
		while( file >> n ) world_info.push_back(n) ;
	}
	for(int i=0; i<world_info.size(); i++)
		std::cout<<world_info[i]<<endl;
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

	int mapEdgeLength=world_info[WI_MAP_SIZE];
		
	world_positions.resize(mapEdgeLength);
	
	
	/**************************
	***fill with empty space***
	**************************/

	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
			world_positions[outerIndex].push_back(0);
	}

	/************************
	***place all entities***
	************************/

	
	PlaceResource(25, 75, ET_TREE);//trees
	PlaceResource(1, 5, ET_IRON);//iron
	PlaceResource(30, 35, ET_STONE);//stone
	PlaceTownCenter();
	PlaceTemple();
	PlaceVillagers(ET_VILLAGER);
	PlaceDomesticBeasts();
	PlaceWildBeasts(0, 8, 0, ET_DEER);//deer
	PlaceWildBeasts(20, 23, 15, ET_WOLF);//wolf
	PlaceWildBeasts(50, 51, 20, ET_OGRE);//ogre
}

void WorldGeneration::PrintMap()
{
	int temp_count=0;
	int sidelength=world_info[WI_MAP_SIZE];
	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			int et_type=world_positions[outerIndex][innerIndex];
			cout<<et_type;
			temp_count=temp_count+1;
			if(temp_count%sidelength==0)
				cout<<endl;
		}
	}
}

void WorldGeneration::PlaceResource(int min, int max, int type)
{
	int temp_random_variable;
	int num_of_resource=0;
	
	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			
			{
				temp_random_variable=rand() % 100;
				if(temp_random_variable>min && temp_random_variable<max)
				{
					world_positions[outerIndex][innerIndex]=type;
					num_of_resource++;
				}
			}
		}
	}
	//cout<<"number of type "<<type<<":"<<num_of_resource<<endl;
}

void WorldGeneration::PlaceTownCenter()
{
	

	/***************************************
	***first team's town center location***
	****************************************/

	TC1_y_coord_topleft=rand() % world_info[WI_MAP_SIZE];	//y-coord
	TC1_x_coord_topleft=rand() % world_info[WI_MAP_SIZE];	//x-coord
	
	/***************************************
	***second team's town center location***
	****************************************/
	
	TC2_y_coord_topleft=rand() % world_info[WI_MAP_SIZE];	//y-coord
	TC2_x_coord_topleft=rand() % world_info[WI_MAP_SIZE];	//x-coord
	
	/*******************************
	***check if TCs are too close***
	*****   move if they are   *****
	********************************/
	
	double x_dist=abs(TC1_x_coord_topleft-TC2_x_coord_topleft);
	double y_dist=abs(TC1_y_coord_topleft-TC2_y_coord_topleft);
	if(sqrt((x_dist * x_dist)+(y_dist * y_dist))<=50)
	{
		if(TC1_y_coord_topleft>TC2_y_coord_topleft)
		{
			TC1_y_coord_topleft=TC1_y_coord_topleft+10;
			TC2_y_coord_topleft=TC2_y_coord_topleft-10;
			if(TC1_y_coord_topleft>world_info[WI_MAP_SIZE])
				TC1_y_coord_topleft=TC1_y_coord_topleft-10;
			if(TC2_y_coord_topleft<0)
				TC2_y_coord_topleft=abs(TC2_y_coord_topleft);

		}
		else
		{
			TC1_y_coord_topleft=TC1_y_coord_topleft-10;
			TC2_y_coord_topleft=TC2_y_coord_topleft+10;
			if(TC1_y_coord_topleft<0)
				TC1_y_coord_topleft=abs(TC1_y_coord_topleft);
			if(TC2_y_coord_topleft>world_info[WI_MAP_SIZE])
				TC2_y_coord_topleft=TC2_y_coord_topleft-10;
		}
	}

	/**************************/
	/***move away from edges***/
	/**************************/
	if(TC1_y_coord_topleft-10<0)
		TC1_y_coord_topleft+=15;
	else if(TC1_y_coord_topleft+10>world_info[WI_MAP_SIZE]-1)
		TC1_y_coord_topleft-=15;

	if(TC1_x_coord_topleft-10<0)
		TC1_x_coord_topleft+=15;
	else if(TC1_x_coord_topleft+10>world_info[WI_MAP_SIZE]-1)
		TC1_x_coord_topleft-=15;

	if(TC2_y_coord_topleft-10<0)
		TC2_y_coord_topleft+=15;
	else if(TC2_y_coord_topleft+10>world_info[WI_MAP_SIZE]-1)
		TC2_y_coord_topleft-=15;

	if(TC2_x_coord_topleft-10<0)
		TC2_x_coord_topleft+=15;
	else if(TC2_x_coord_topleft+10>world_info[WI_MAP_SIZE]-1)
		TC2_x_coord_topleft-=15;

	/***************************/
	/***check closeness again***/
	/***************************/

	if(sqrt((x_dist * x_dist)+(y_dist * y_dist))<=50)
	{
		if(TC1_x_coord_topleft>TC2_x_coord_topleft)
		{
			TC1_x_coord_topleft+=10;
			TC2_x_coord_topleft-=10;
			if(TC1_x_coord_topleft>world_info[WI_MAP_SIZE])
				TC1_x_coord_topleft-=10;
			if(TC2_x_coord_topleft<0)
				TC2_x_coord_topleft=abs(TC2_x_coord_topleft);

		}
		else
		{
			TC1_x_coord_topleft-=10;
			TC2_x_coord_topleft+=10;
			if(TC1_x_coord_topleft<0)
				TC1_x_coord_topleft=abs(TC1_x_coord_topleft);
			if(TC2_x_coord_topleft>world_info[WI_MAP_SIZE])
				TC2_x_coord_topleft-=10;
		}
	}

	/**************************/
	/***move away from edges***/
	/**************************/

	if(TC1_y_coord_topleft-10<0)
		TC1_y_coord_topleft+=15;
	else if(TC1_y_coord_topleft+10>world_info[WI_MAP_SIZE]-1)
		TC1_y_coord_topleft-=15;

	if(TC1_x_coord_topleft-10<0)
		TC1_x_coord_topleft+=15;
	else if(TC1_x_coord_topleft+10>world_info[WI_MAP_SIZE]-1)
		TC1_x_coord_topleft-=15;

	if(TC2_y_coord_topleft-10<0)
		TC2_y_coord_topleft+=15;
	else if(TC2_y_coord_topleft+10>world_info[WI_MAP_SIZE]-1)
		TC2_y_coord_topleft-=15;

	if(TC2_x_coord_topleft-10<0)
		TC2_x_coord_topleft+=15;
	else if(TC2_x_coord_topleft+10>world_info[WI_MAP_SIZE]-1)
		TC2_x_coord_topleft-=15;

	/**********************/
	/***clear TC1's area***/
	/**********************/

	for(int outerIndex=TC1_y_coord_topleft-7; outerIndex<TC1_y_coord_topleft+7; outerIndex++)
	{
		for(int innerIndex=TC1_x_coord_topleft-7; innerIndex<TC1_x_coord_topleft+7; innerIndex++)
		{
			world_positions[outerIndex][innerIndex]=0;
		}
	}
	/**********************/
	/***clear TC2's area***/
	/**********************/
	for(int outerIndex=TC2_y_coord_topleft-7; outerIndex<TC2_y_coord_topleft+7; outerIndex++)
	{
		for(int innerIndex=TC2_x_coord_topleft-7; innerIndex<TC2_x_coord_topleft+7; innerIndex++)
		{
			world_positions[outerIndex][innerIndex]=0;
		}
	}

	/**************************/
	/***set locations of TCs***/
	/**************************/	

	world_positions[TC1_y_coord_topleft][TC1_x_coord_topleft]=ET_TOWN_CENTER;// team 1 
	world_positions[TC2_y_coord_topleft][TC2_x_coord_topleft]=ET_TOWN_CENTER_CC;// team 2
}

void WorldGeneration::PlaceTemple()
{
	/*offsetting the temple from the town center:
	0=north
	1=south
	2=east
	3=west
	3 tiles north or south and 3 tiles east or west*/

	/******************/
	/***find offsets***/
	/******************/

	int x_offset1;
	int y_offset1;
	int x_offset2;
	int y_offset2;

	int x_offset1_dir=rand()%100;
	if(x_offset1_dir>=0 && x_offset1_dir<50)
		x_offset1=-3;
	if(x_offset1_dir>=50 && x_offset1_dir<99)
		x_offset1=3;
	
	int y_offset1_dir=rand()%100;
	if(y_offset1_dir>=0 && y_offset1_dir<50)
		y_offset1=-3;
	if(y_offset1_dir>=50 && y_offset1_dir<99)
		y_offset1=3;
	
	int x_offset2_dir=rand()%100;
	if(x_offset2_dir>=0 && x_offset2_dir<50)
		x_offset2=-3;
	if(x_offset2_dir>=50 && x_offset2_dir<99)
		x_offset2=3;

	int y_offset2_dir=rand()%100;
	if(y_offset2_dir>=0 && y_offset2_dir<50)
		y_offset2=-3;
	if(y_offset2_dir>=50 && y_offset2_dir<99)
		y_offset2=3;
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
	world_positions[TC1_y_coord_topleft+y_offset1][TC1_x_coord_topleft+x_offset1]=ET_TEMPLE;//team 1
	world_positions[TC2_y_coord_topleft+y_offset2][TC2_x_coord_topleft+x_offset2]=ET_TEMPLE;//team 2
}

void WorldGeneration::PlaceVillagers(int type)
{
	int team1_villager_count=0;
	int team2_villager_count=0;
		
	/*********************************************************/
	/***placing villagers around the town center and shrine***/
	/*********************************************************/
	/***team 1***/

	for(int outerIndex=TC1_y_coord_topleft-3; outerIndex<=TC1_y_coord_topleft+3; outerIndex++)
	{
		for(int innerIndex=TC1_x_coord_topleft-5; innerIndex<TC1_x_coord_topleft+5; innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==0 && team1_villager_count < world_info[WI_NUM_OF_VILLAGERS])
			{
				world_positions[outerIndex][innerIndex]=type;
				team1_villager_count++;
			}
		}
	}

	/***team 2***/
	
	for(int outerIndex=TC2_y_coord_topleft-3; outerIndex<=TC2_y_coord_topleft+3; outerIndex++)
	{
		for(int innerIndex=TC2_x_coord_topleft-5; innerIndex<TC2_x_coord_topleft+5; innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==0 && team2_villager_count < world_info[WI_NUM_OF_VILLAGERS])
			{
				world_positions[outerIndex][innerIndex]=type;
				team2_villager_count++;
			}
		}
	}
	
}

void WorldGeneration::PlaceDomesticBeasts()
{
	//int team1_type_count=0;
	//int team2_type_count=0;
	
	int temp_type=ET_COW;
	/****************************************************/
	/***placing domestic beasts around the town center and temple***/
	/****************************************************/
	/***team 1***/

	for(int counter=0; counter<world_info.size()-3;  counter++)
	{
		int team1_type_count=0;
		for(int outerIndex=TC1_y_coord_topleft-3; outerIndex<=TC1_y_coord_topleft+3; outerIndex++)
		{
			for(int innerIndex=TC1_x_coord_topleft-5; innerIndex<TC1_x_coord_topleft+5; innerIndex++)
			{
				if(world_positions[outerIndex][innerIndex]==0 && team1_type_count < world_info[WI_NUM_OF_COWS+counter])
				{
					world_positions[outerIndex][innerIndex]=temp_type;
					team1_type_count++;
				}
			}
		}
	
	temp_type++;
	}

	/***team 2***/
	temp_type=ET_COW;
	

	for(int counter=0; counter<world_info.size()-3;  counter++)
	{
		int team2_type_count=0;
		for(int outerIndex=TC2_y_coord_topleft-3; outerIndex<=TC2_y_coord_topleft+3; outerIndex++)
		{
			for(int innerIndex=TC2_x_coord_topleft-5; innerIndex<TC2_x_coord_topleft+5; innerIndex++)
			{
				if(world_positions[outerIndex][innerIndex]==0 && team2_type_count < world_info[WI_NUM_OF_COWS+counter])
				{
					world_positions[outerIndex][innerIndex]=temp_type;
					team2_type_count++;
				}
			}
		}
	
	temp_type++;
	}
}

void WorldGeneration::PlaceWildBeasts(int min, int max, int delete_chance, int type)
{
	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			int chance_for_entity=rand() % 100;
			if(world_positions[outerIndex][innerIndex]==0 && chance_for_entity>=min && chance_for_entity<max)
			{
				
				world_positions[outerIndex][innerIndex]=type;

				double x1_dist=abs(innerIndex-TC1_x_coord_topleft);//removing if too close to TC
				double y1_dist=abs(outerIndex-TC1_y_coord_topleft);
				double x2_dist=abs(innerIndex-TC2_x_coord_topleft);
				double y2_dist=abs(outerIndex-TC2_y_coord_topleft);

				
				int chance_to_delete=rand() % 100;

				if(sqrt((x1_dist * x1_dist)+(y1_dist * y1_dist))<=20.0 || sqrt((x2_dist * x2_dist)+(y2_dist * y2_dist))<=20.0 || chance_to_delete<=delete_chance)
				{
					world_positions[outerIndex][innerIndex]=0;
				}
			}
		}
	}
}