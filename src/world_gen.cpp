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
	time_t timer;
	srand(time(&timer));//rand must be seeded before placement, if not here then in another module that needs it first
	//if it is used I will remove it from this location

	entityCount=0;
	current.x=0;
	current.y=0;
	cycled=false;

	/*****************
	***get map info***
	*****************/

		ifstream file("worldInfo.txt");
		int n;
		while( file >> n ) world_info.push_back(n);
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
			world_positions[outerIndex].push_back(ET_NONE);
	}

	/************************
	***place all entities***
	************************/

	PlaceResource(25, 75, ET_TREE);//trees
	PlaceResource(1, 5, ET_IRON);//iron
	PlaceResource(30, 35, ET_STONE);//stone
	PlaceTownCenter();
	PlaceTemple();
	PlaceVillagers(ET_VILLAGER, TC1);
	PlaceVillagers(ET_VILLAGER, TC2);
	PlaceDomesticBeasts(ET_COW, WI_NUM_OF_COWS, TC1);
	PlaceDomesticBeasts(ET_COW, WI_NUM_OF_COWS, TC2);
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

void WorldGeneration::PlaceResource(int min, int max, EntityType type)
{
	int temp_random_variable;
	int num_of_resource=0;

	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			temp_random_variable=rand() % 100;
			if(temp_random_variable>min && temp_random_variable<max)
			{
				world_positions[outerIndex][innerIndex]=type;
				num_of_resource++;
				entityCount++;
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

	TC1.y=rand() % world_info[WI_MAP_SIZE];	//y-coord
	TC1.x=rand() % world_info[WI_MAP_SIZE];	//x-coord

	/***************************************
	***second team's town center location***
	****************************************/

	TC2.y=rand() % world_info[WI_MAP_SIZE];	//y-coord
	TC2.x=rand() % world_info[WI_MAP_SIZE];	//x-coord

	/*******************************
	***check if TCs are too close***
	*****   move if they are   *****
	********************************/
	if(TC1.distance(TC2)<=50)
	{
		if(TC1.y>TC2.y)
		{
			TC1.y+=10;
			TC2.y-=10;
			if(TC1.y>world_info[WI_MAP_SIZE])
				TC1.y-=10;
			if(TC2.y<0)
				TC2.y+=10;
		}
		// The following block of code is the same as above.
		// Refactor this.
		else
		{
			TC1.y-=10;
			TC2.y+=10;
			if(TC1.y<0)
				TC1.y+=10;
			if(TC2.y>world_info[WI_MAP_SIZE])
				TC2.y-=10;
		}
	}

	/**************************/
	/***move away from edges***/
	/**************************/
	TC1.y=shiftFromEdge(TC1.y);
	TC1.x=shiftFromEdge(TC1.x);
	TC2.y=shiftFromEdge(TC2.y);
	TC2.x=shiftFromEdge(TC2.x);
	// The following block of code is the same as above.
	// Refactor this.
	/***************************/
	/***check closeness again***/
	/***************************/

	if(TC1.distance(TC2)<=50)
	{
		if(TC1.x>TC2.x)
		{
			TC1.x+=10;
			TC2.x-=10;
			if(TC1.x>world_info[WI_MAP_SIZE])
				TC1.x-=10;
			if(TC2.x<0)
				TC2.x+=10;
		}
		// The following block of code is the same as above.
		// Refactor this.
		else
		{
			TC1.x-=10;
			TC2.x+=10;
			if(TC1.x<0)
				TC1.x+=10;
			if(TC2.x>world_info[WI_MAP_SIZE])
				TC2.x-=10;
		}
	}

	/**************************/
	/***move away from edges***/
	/**************************/
	TC1.y=shiftFromEdge(TC1.y);
	TC1.x=shiftFromEdge(TC1.x);
	TC2.y=shiftFromEdge(TC2.y);
	TC2.x=shiftFromEdge(TC2.x);
	/**********************/
	/***clear TC1's area***/
	/**********************/
	clearArea(TC1);
	clearArea(TC2);
	/**************************/
	/***set locations of TCs***/
	/**************************/

	world_positions[TC1.y][TC1.x]=ET_TOWN_CENTER;// team 1
	entityCount++;
	world_positions[TC2.y][TC2.x]=ET_TOWN_CENTER;// team 2
	entityCount++;
}

void WorldGeneration::PlaceTemple()
{
	/******************/
	/***find offsets***/
	/******************/

	int x_offset1=findOffset();
	int y_offset1=findOffset();
	int x_offset2=findOffset();
	int y_offset2=findOffset();
	/**********************************/
	/***use offsets to place temples***/
	/**********************************/
	world_positions[TC1.y+y_offset1][TC1.x+x_offset1]=ET_TEMPLE;//team 1
	entityCount++;
	world_positions[TC2.y+y_offset2][TC2.x+x_offset2]=ET_TEMPLE;//team 2
	entityCount++;
}

void WorldGeneration::PlaceVillagers(EntityType type, Position pos)
{
	int team_villager_count=0;	

	/*********************************************************/
	/***placing villagers around the town center and shrine***/
	/*********************************************************/

	for(int outerIndex=pos.y-3; outerIndex<=pos.y+3; outerIndex++)
	{
		for(int innerIndex=pos.x-5; innerIndex<pos.x+5; innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==0 && team_villager_count < world_info[WI_NUM_OF_VILLAGERS])
			{
				world_positions[outerIndex][innerIndex]=type;
				team_villager_count++;
				entityCount++;
			}
		}
	}
}

void WorldGeneration::PlaceDomesticBeasts(EntityType type, int number, Position pos)
{
	int team_type_count=0;
	for(int outerIndex=pos.y-3; outerIndex<=pos.y+3; outerIndex++)
	{
		for(int innerIndex=pos.x-5; innerIndex<pos.x+5; innerIndex++)
		{
			if(world_positions[outerIndex][innerIndex]==0 && team_type_count < world_info[number])
			{
				world_positions[outerIndex][innerIndex]=type;
				team_type_count++;
				entityCount++;
			}
		}
	}
}

void WorldGeneration::PlaceWildBeasts(int min, int max, int delete_chance, EntityType type)
{
	for(int outerIndex=0; outerIndex<world_positions.size(); outerIndex++)
	{
		for(int innerIndex=0; innerIndex<world_positions.size(); innerIndex++)
		{
			int chance_for_entity=rand() % 100;
			if(world_positions[outerIndex][innerIndex]==0 && chance_for_entity>=min && chance_for_entity<max)
			{
				world_positions[outerIndex][innerIndex]=type;
				entityCount++;

				double x1_dist=abs(innerIndex-TC1.x);//removing if too close to TC
				double y1_dist=abs(outerIndex-TC1.y);
				double x2_dist=abs(innerIndex-TC2.x);
				double y2_dist=abs(outerIndex-TC2.y);

				int chance_to_delete=rand() % 100;

				if(sqrt((x1_dist * x1_dist)+(y1_dist * y1_dist))<=20.0 || sqrt((x2_dist * x2_dist)+(y2_dist * y2_dist))<=20.0 || chance_to_delete<=delete_chance)
				{
					world_positions[outerIndex][innerIndex]=ET_NONE;
					entityCount--;
				}
			}
		}
	}
}

Entity WorldGeneration::getNextEntity()
{
	Entity to_return(ET_NONE,0,current,FT_NONE);
	while(true)
	{
		if(world_positions[current.y][current.x]==0)
		{
			if(current.y==world_positions.size()-1 && current.x==world_positions.size()-1)
				throw ("noMoreEntities");
			else if(cycled==true)
				throw ("noMoreEntities");
			else
				nextPosition();
		}
		else if(world_positions[current.y][current.x]!=0)
		{
			if(cycled==true)
				throw ("noMoreEntities");
			else
			{
			to_return.setEntityType(world_positions[current.y][current.x]);

			//switch(world_positions[current.y][current.x])
			//{
			//case ET_VILLAGER:
			//case ET_COW:
			//case ET_DEER:
			//case ET_TREE:
			//case ET_IRON:
			//case ET_STONE:
			//case ET_WOLF:
			//	// to_return.setMaxHealth(100); // This is outside of world gen's scope.
			//	break;
			//case ET_OGRE:
			//	// to_return.setMaxHealth(250); // This is outside of world gen's scope.
			//	break;
			//default:
			//	// to_return.setMaxHealth(0); // This is outside of world gen's scope.
			//	break;
			//}

			to_return.setPosition(current);

			if(world_positions[current.y][current.x]==ET_TREE ||
				world_positions[current.y][current.x]==ET_STONE ||
				world_positions[current.y][current.x]==ET_IRON ||
				world_positions[current.y][current.x]==ET_DEER ||
				world_positions[current.y][current.x]==ET_WOLF ||
				world_positions[current.y][current.x]==ET_OGRE)
			{
				// to_return.setFaction(0); // Should be the default.
			}
			else
			{
				double x_dist=abs(TC1.x-current.x);
				double y_dist=abs(TC1.y-current.y);
				double length_to_tc1=sqrt((x_dist * x_dist)+(y_dist * y_dist));

				x_dist=abs(TC2.x-current.x);
				y_dist=abs(TC2.y-current.y);
				double length_to_tc2=sqrt((x_dist * x_dist)+(y_dist * y_dist));
				if(length_to_tc1<length_to_tc2)
					to_return.setFactionType(FT_PLAYER_1);
				else
					to_return.setFactionType(FT_PLAYER_2);
			}
			nextPosition();
			return to_return;
		}
		}
	}

}

int WorldGeneration::getEntityCount()
{
	return entityCount;
}

void WorldGeneration::nextPosition()
{
	if(current.x==world_positions.size()-1 && current.y==world_positions.size()-1)
	{
		current.x=0;
		current.y=0;
		cycled=true;
	}
	else if(current.x==world_positions.size()-1)
	{
		current.x=0;
		current.y++;
	}
	else
	{
		current.x++;
		current.y++;
	}
}

int WorldGeneration::findOffset()
{
	int x=rand()%100;
	if(x>=0 && x<50)
		return -3;
	if(x>=50 && x<100)
		return 3;
}

int WorldGeneration::shiftFromEdge(int coord)
{
	if(coord-7<0)
		return coord+=14;
	else if(coord+7>world_info[WI_MAP_SIZE]-1)
		return coord-=14;
}

void WorldGeneration::clearArea(Position pos)
{
	for(int outerIndex=pos.y-7; outerIndex<pos.y+7; outerIndex++)
	{
		for(int innerIndex=pos.x-7; innerIndex<pos.x+7; innerIndex++)
		{
			world_positions[outerIndex][innerIndex]=ET_NONE;
		}
	}
}
