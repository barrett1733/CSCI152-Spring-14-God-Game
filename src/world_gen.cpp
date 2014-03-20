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
	world_info;
	world_positions;

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
	int mapsize_index=0;//the number is the index of the variable name, aka the line number in the text file
	int difficulty_index=1;
	int villagers_index=2;
	int cows_index=3;

	int mapEdgeLength=world_info[mapsize_index];
		
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

	void PlaceTrees();
	void PlaceStone();
	void PlaceIron();
	void PlaceTownCenter();
	void PlaceShrine();
	void PlaceEntities();
}

//void WorldGeneration::SizeMap()
//{
///*************************************************
//        get world info from text file
//*************************************************/	
//	ifstream myReadFile;
//	void read_from_file();
//	{
//		ifstream file("worldInfo.txt");
//		int n;
//		while( file >> n ) world_info.push_back(n) ;
//	}
//	for(int i=0; i<world_info.size(); i++)
//		std::cout<<world_info[i]<<endl;
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//	int mapsize_index=0;//the number is the index of the variable name, aka the line number in the text file
//	int difficulty_index=1;
//	int villagers_index=2;
//	int cows_index=3;
//
//	int mapEdgeLength=world_info[mapsize_index];
//		
//	world_positions.resize(mapEdgeLength);
//}

//void WorldGeneration::PlaceEmptySpace()
//{
//	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
//	{
//		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
//			world_positions[outerIndex].push_back(Entity(ET_NONE, 0, innerIndex, outerIndex));
//	}
//}

void WorldGeneration::PrintMap()
{
	int mapsize_index=0;//the number is the index of the variable name, aka the line number in the text file
	int difficulty_index=1;
	int villagers_index=2;
	int cows_index=3;
	int temp_count=0;
	int sidelength=world_info[mapsize_index];
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

void WorldGeneration::PlaceTrees()
{
	int temp_random_variable;
	time_t timer;
	int num_of_trees=0;
	
	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			
			{
			temp_random_variable=rand() % 100;
			if(temp_random_variable>25 && temp_random_variable<75)
			{
				world_positions[outerIndex][innerIndex]=1;
				num_of_trees++;
			}
			}
		}
	}
	//cout<<"number of trees: "<<num_of_trees<<endl;
}

void WorldGeneration::PlaceIron()
{
	int temp_random_variable;
	time_t timer;
	int num_of_iron=0;

	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			temp_random_variable=rand() % 100;
			
			if(temp_random_variable>1 && temp_random_variable<5)
			{
				world_positions[outerIndex][innerIndex]=7;
				num_of_iron++;
			}
		}
	}
	//cout<<"number of iron: "<<num_of_iron<<endl;
}

void WorldGeneration::PlaceStone()
{
	int temp_random_variable;
	time_t timer;
	int num_of_stone=0;

	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			temp_random_variable=rand() % 100;
			if(temp_random_variable>30 && temp_random_variable<35)
			{
				world_positions[outerIndex][innerIndex]=5;
				num_of_stone++;
			}
		}
	}
	//cout<<"number of stone: "<<num_of_stone<<endl;
}

void WorldGeneration::PlaceTownCenter()
{
	int mapsize_index=0;//the number is the index of the variable name, aka the line number in the text file
	int difficulty_index=1;
	int villagers_index=2;
	int cows_index=3;

	int temp_random_variable;
	time_t timer;
	time(&timer);

	/***************************************
	***first team's town center location***
	****************************************/

	temp_random_variable=difftime(timer,(timer+rand()%1000));
	double TC1_outerIndex=rand() % world_info[mapsize_index];	//y-coord	
	
	temp_random_variable=difftime(timer,(timer+rand()%1000));
	double TC1_innerIndex=rand() % world_info[mapsize_index];	//x-coord
	

	/***************************************
	***second team's town center location***
	****************************************/
	
	temp_random_variable=difftime(timer,(timer+rand()%1000));
	double TC2_outerIndex=rand() % world_info[mapsize_index];	//y-coord
	
	temp_random_variable=difftime(timer,(timer+rand()%1000));
	double TC2_innerIndex=rand() % world_info[mapsize_index];	//x-coord

	//cout<<endl<<TC1_innerIndex<<","<<TC1_outerIndex<<endl;
	//cout<<endl<<TC2_innerIndex<<","<<TC2_outerIndex<<endl;
	

	/*******************************
	***check if TCs are too close***
	*****   move if they are   *****
	********************************/
	
	double x_dist=abs(TC1_innerIndex-TC2_innerIndex);
	double y_dist=abs(TC1_outerIndex-TC2_outerIndex);
	if(sqrt((x_dist * x_dist)+(y_dist * y_dist))<=50)
	{
		if(TC1_outerIndex>TC2_outerIndex)
		{
			TC1_outerIndex=TC1_outerIndex+10;
			TC2_outerIndex=TC2_outerIndex-10;
			if(TC1_outerIndex>world_info[mapsize_index])
				TC1_outerIndex=TC1_outerIndex-10;
			if(TC2_outerIndex<0)
				TC2_outerIndex=abs(TC2_outerIndex);

		}
		else
		{
			TC1_outerIndex=TC1_outerIndex-10;
			TC2_outerIndex=TC2_outerIndex+10;
			if(TC1_outerIndex<0)
				TC1_outerIndex=abs(TC1_outerIndex);
			if(TC2_outerIndex>world_info[mapsize_index])
				TC2_outerIndex=TC2_outerIndex-10;
		}
	}

	/*************************
	***move away from edges***
	**************************/
	if(TC1_outerIndex-10<0)
		TC1_outerIndex=TC1_outerIndex+15;
	else if(TC1_outerIndex+10>world_info[mapsize_index]-1)
		TC1_outerIndex=TC1_outerIndex-15;

	if(TC1_innerIndex-10<0)
		TC1_innerIndex=TC1_innerIndex+15;
	else if(TC1_innerIndex+10>world_info[mapsize_index]-1)
		TC1_innerIndex=TC1_innerIndex-15;

	if(TC2_outerIndex-10<0)
		TC2_outerIndex=TC2_outerIndex+15;
	else if(TC2_outerIndex+10>world_info[mapsize_index]-1)
		TC2_outerIndex=TC2_outerIndex-15;

	if(TC2_innerIndex-10<0)
		TC2_innerIndex=TC2_innerIndex+15;
	else if(TC2_innerIndex+10>world_info[mapsize_index]-1)
		TC2_innerIndex=TC2_innerIndex-15;

	/**************************
	***check closeness again***
	***************************/

	if(sqrt((x_dist * x_dist)+(y_dist * y_dist))<=50)
	{
		if(TC1_innerIndex>TC2_innerIndex)
		{
			TC1_innerIndex=TC1_innerIndex+10;
			TC2_innerIndex=TC2_innerIndex-10;
			if(TC1_innerIndex>world_info[mapsize_index])
				TC1_innerIndex=TC1_innerIndex-10;
			if(TC2_innerIndex<0)
				TC2_innerIndex=abs(TC2_innerIndex);

		}
		else
		{
			TC1_innerIndex=TC1_innerIndex-10;
			TC2_innerIndex=TC2_innerIndex+10;
			if(TC1_innerIndex<0)
				TC1_innerIndex=abs(TC1_innerIndex);
			if(TC2_innerIndex>world_info[mapsize_index])
				TC2_innerIndex=TC2_innerIndex-10;
		}
	}

	/*************************
	***move away from edges***
	**************************/

	if(TC1_outerIndex-10<0)
		TC1_outerIndex=TC1_outerIndex+15;
	else if(TC1_outerIndex+10>world_info[mapsize_index]-1)
		TC1_outerIndex=TC1_outerIndex-15;

	if(TC1_innerIndex-10<0)
		TC1_innerIndex=TC1_innerIndex+15;
	else if(TC1_innerIndex+10>world_info[mapsize_index]-1)
		TC1_innerIndex=TC1_innerIndex-15;

	if(TC2_outerIndex-10<0)
		TC2_outerIndex=TC2_outerIndex+15;
	else if(TC2_outerIndex+10>world_info[mapsize_index]-1)
		TC2_outerIndex=TC2_outerIndex-15;

	if(TC2_innerIndex-10<0)
		TC2_innerIndex=TC2_innerIndex+15;
	else if(TC2_innerIndex+10>world_info[mapsize_index]-1)
		TC2_innerIndex=TC2_innerIndex-15;

	/*************************
	***set locations of TCs***
	**************************/
	

	world_positions[TC1_outerIndex][TC1_innerIndex]=65537;// 1 set that location to the integer that represents team 1's
	//cout<<endl<<TC1_innerIndex<<","<<TC1_outerIndex<<endl;// town center
	world_positions[TC2_outerIndex][TC2_innerIndex]=65538;// 2 set that location to the integer that represents team 2's
	//cout<<endl<<TC2_innerIndex<<","<<TC2_outerIndex<<endl;// town center

	/*********************
	***clear TC1's area***
	**********************/
	
	for(int outerIndex=TC1_outerIndex-7; outerIndex<TC1_outerIndex+7; outerIndex++)
	{
		for(int innerIndex=TC1_innerIndex-7; innerIndex<TC1_innerIndex+7; innerIndex++)
		{
			if(innerIndex==TC1_innerIndex && outerIndex==TC1_outerIndex) 
				world_positions[outerIndex][innerIndex]=65537;
			else if(innerIndex==TC2_innerIndex && outerIndex==TC2_outerIndex)
				world_positions[outerIndex][innerIndex]=65538;
			else
				world_positions[outerIndex][innerIndex]=0;
		}
	}
	/*********************
	***clear TC2's area***
	**********************/
	for(int outerIndex=TC2_outerIndex-7; outerIndex<TC2_outerIndex+7; outerIndex++)
	{
		for(int innerIndex=TC2_innerIndex-7; innerIndex<TC2_innerIndex+7; innerIndex++)
		{
			if(innerIndex==TC1_innerIndex && outerIndex==TC1_outerIndex) //1
				world_positions[outerIndex][innerIndex]=65537;//1
			else if(innerIndex==TC2_innerIndex && outerIndex==TC2_outerIndex)//2
				world_positions[outerIndex][innerIndex]=65538;//2
			else
				world_positions[outerIndex][innerIndex]=0;
		}
	}	
}

void WorldGeneration::PlaceTemple()
{
	int temp_random_variable;
	time_t timer;
	time(&timer);
	/*offsetting the temple from the town center:
	0=north
	1=south
	2=east
	3=west
	3 tiles north or south and 3 tiles east or west*/

	int x_offset1=1;
	int y_offset1=1;
	int x_offset2=1;
	int y_offset2=1;

	temp_random_variable=difftime(timer,(timer+rand()%1000));
	int x_offset1_dir=rand()%100;
	if(x_offset1_dir>=0 && x_offset1_dir<50)
		x_offset1=-3;
	if(x_offset1_dir>=50 && x_offset1_dir<99)
		x_offset1=3;
	

	temp_random_variable=difftime(timer,(timer+rand()%1000));
	int y_offset1_dir=rand()%100;
	if(y_offset1_dir>=0 && y_offset1_dir<50)
		y_offset1=-3;
	if(y_offset1_dir>=50 && y_offset1_dir<99)
		y_offset1=3;
	

	temp_random_variable=difftime(timer,(timer+rand()%1000));
	int x_offset2_dir=rand()%100;
	if(x_offset2_dir>=0 && x_offset2_dir<50)
		x_offset2=-3;
	if(x_offset2_dir>=50 && x_offset2_dir<99)
		x_offset2=3;

	temp_random_variable=difftime(timer,(timer+rand()%1000));
	int y_offset2_dir=rand()%100;
	if(y_offset2_dir>=0 && y_offset2_dir<50)
		y_offset2=-3;
	if(y_offset2_dir>=50 && y_offset2_dir<99)
		y_offset2=3;



	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
			if(world_positions[outerIndex][innerIndex]==65537 && !65538)//1
			{
				world_positions[outerIndex+y_offset1][innerIndex+x_offset1]=65547;//1
			}
	}

	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
			if(world_positions[outerIndex][innerIndex]==65538)//2
			{
				world_positions[outerIndex+y_offset2][innerIndex+x_offset2]=65547;//2
			}
	}
	//cout<<endl<<"shrine offsets:"<<endl<<"x1: "<<x_offset1<<" y1: "<<y_offset1<<endl<<"x2: "<<x_offset2<<" y2: "<<y_offset2<<endl;
}

void WorldGeneration::PlaceEntities()
{
	int mapsize_index=0;//the number is the index of the variable name, aka the line number in the text file
	int difficulty_index=1;
	int villagers_index=2;
	int cows_index=3;
	int TC1_x_coord_topleft;
	int TC1_y_coord_topleft;
	int TC2_x_coord_topleft;
	int TC2_y_coord_topleft;
	int team1_villager_count=0;
	int team2_villager_count=0;
	int team1_cow_count=0;
	int team2_cow_count=0;
	int num_of_ogres=0;
	int num_of_deer=0;
	int num_of_wolves=0;

	/*find the team 1 Town center*/

	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==65537)
			{
				TC1_x_coord_topleft=innerIndex;
				TC1_y_coord_topleft=outerIndex;
			}
		}
	}

	/*find the team 2 Town center*/

	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==65538)
			{
				TC2_x_coord_topleft=innerIndex;
				TC2_y_coord_topleft=outerIndex;
			}
		}
	}

	/*********************************************************/
	/***placing villagers around the town center and shrine***/
	/*********************************************************/
	/***team 1***/

	for(int outerIndex=TC1_y_coord_topleft-3; outerIndex<=TC1_y_coord_topleft+3; outerIndex++)
	{
		for(int innerIndex=TC1_x_coord_topleft-5; innerIndex<TC1_x_coord_topleft+5; innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==0 && team1_villager_count <= world_info[villagers_index])
			{
				world_positions[outerIndex][innerIndex]=256;
				team1_villager_count++;
			}
		}
	}

	/***team 2***/
	
	for(int outerIndex=TC2_y_coord_topleft-3; outerIndex<=TC2_y_coord_topleft+3; outerIndex++)
	{
		for(int innerIndex=TC2_x_coord_topleft-5; innerIndex<TC2_x_coord_topleft+5; innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==0 && team2_villager_count <= world_info[villagers_index])
			{
				world_positions[outerIndex][innerIndex]=256;
				team2_villager_count++;
			}
		}
	}
	/*********************************************************/
	/***placing cows around the town center and shrine***/
	/*********************************************************/
	/***team 1***/

	for(int outerIndex=TC1_y_coord_topleft-3; outerIndex<=TC1_y_coord_topleft+3; outerIndex++)
	{
		for(int innerIndex=TC1_x_coord_topleft-5; innerIndex<TC1_x_coord_topleft+5; innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==0 && team1_cow_count <= world_info[cows_index])
			{
				Position TC1; 
				TC1.x=TC1_x_coord_topleft;
				TC1.y=TC1_y_coord_topleft;
				world_positions[outerIndex][innerIndex]=259;
				team1_cow_count++;
			}
		}
	}

	/***team 2***/

	for(int outerIndex=TC2_y_coord_topleft-3; outerIndex<=TC2_y_coord_topleft+3; outerIndex++)
	{
		for(int innerIndex=TC2_x_coord_topleft-5; innerIndex<TC2_x_coord_topleft+5; innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==0 && team2_cow_count <= world_info[cows_index])
			{
				Position TC2; 
				TC2.x=TC2_x_coord_topleft;
				TC2.y=TC2_y_coord_topleft;
				world_positions[outerIndex][innerIndex]=259;
				team2_cow_count++;
			}
		}
	}

	/***randomly placing deer, wolves and ogres***/

	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			int chance_for_entity=rand() % 100;
			if(world_positions[outerIndex][innerIndex]==0 && chance_for_entity>=0 && chance_for_entity<8)
			{
				world_positions[outerIndex][innerIndex]=265;
				num_of_deer++;

				double x1_dist=abs(innerIndex-TC1_x_coord_topleft);//removing if too close to TC
				double y1_dist=abs(outerIndex-TC1_y_coord_topleft);
				double x2_dist=abs(innerIndex-TC2_x_coord_topleft);
				double y2_dist=abs(outerIndex-TC2_y_coord_topleft);
				if(sqrt((x1_dist * x1_dist)+(y1_dist * y1_dist))<=15 || sqrt((x2_dist * x2_dist)+(y2_dist * y2_dist))<=15)
				{
					world_positions[outerIndex][innerIndex]=0;
					num_of_deer--;
				}
			}
			else if(world_positions[outerIndex][innerIndex]==0 && chance_for_entity>=20 && chance_for_entity<23)
			{
				world_positions[outerIndex][innerIndex]=266;
				num_of_wolves++;

				double x1_dist=abs(innerIndex-TC1_x_coord_topleft);//removing if too close to TC
				double y1_dist=abs(outerIndex-TC1_y_coord_topleft);
				double x2_dist=abs(innerIndex-TC2_x_coord_topleft);
				double y2_dist=abs(outerIndex-TC2_y_coord_topleft);

				
				int chance_to_delete=rand() % 100;

				if(sqrt((x1_dist * x1_dist)+(y1_dist * y1_dist))<=20.0 || sqrt((x2_dist * x2_dist)+(y2_dist * y2_dist))<=20.0 || (chance_to_delete>=5 && chance_to_delete<=20))
				{
					world_positions[outerIndex][innerIndex]=0;
					num_of_wolves--;
				}
			}
			else if(world_positions[outerIndex][innerIndex]==0 && chance_for_entity>=50 && chance_for_entity<51)
			{
				world_positions[outerIndex][innerIndex]=267;
				num_of_ogres++;

				double x1_dist=abs(innerIndex-TC1_x_coord_topleft);//removing if too close to TC
				double y1_dist=abs(outerIndex-TC1_y_coord_topleft);
				double x2_dist=abs(innerIndex-TC2_x_coord_topleft);
				double y2_dist=abs(outerIndex-TC2_y_coord_topleft);

				int chance_to_delete=rand() % 100;

				if(sqrt((x1_dist * x1_dist)+(y1_dist * y1_dist))<=20.0 || sqrt((x2_dist * x2_dist)+(y2_dist * y2_dist))<=20.0 || (chance_to_delete>20 && chance_to_delete<40))
				{
					world_positions[outerIndex][innerIndex]=0;
					num_of_ogres--;
				}
			}
		}
	}
	//cout<<endl<<"number of deer: "<<num_of_deer<<endl<<"number of wolves: "<<num_of_wolves<<endl<<"number of ogres: "<<num_of_ogres<<endl;
}


