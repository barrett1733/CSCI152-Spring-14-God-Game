//
//  File: world-gen.cpp
//  Author: Robert Boettcher
//  CSci 152
//  Spring 2014
//
// Implementation of world gen
//
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>
#include <cmath>
#include <string>
#include "world-gen.h"

using namespace std;

WorldGeneration::~WorldGeneration(){}

WorldGeneration::WorldGeneration() :
	current(0,0)
{

	entityCount = 0;
	cycled = false;
	world_info.resize(WI_COUNT);

	/*****************
	******config******
	*****************/
	load("res/world-info.cfg");

	srand(world_info[WI_SEED]);

	if (world_info[WI_MAP_SIZE] < 40) world_info[WI_MAP_SIZE] = 40;

	world_positions.resize(world_info[WI_MAP_SIZE]);
	Position::max_x = Position::max_y = world_info[WI_MAP_SIZE] - 1;

	/**************************
	***fill with empty space***
	**************************/

	for(int outerIndex = 0; outerIndex < world_positions.size(); outerIndex++)
	{
		for(int innerIndex = 0; innerIndex < world_positions.size(); innerIndex++)
			world_positions[outerIndex].push_back(ET_NONE);
	}

	/************************
	***place all entities***
	************************/
	PlaceResource(WI_TREES_MIN, WI_TREES_MAX, ET_TREE);
	PlaceResource(WI_IRON_MIN, WI_IRON_MAX, ET_IRON);
	PlaceResource(WI_STONE_MIN, WI_STONE_MAX, ET_STONE);
	
	placePaths();//comment this out and uncomment placePaths2 in the PlaceTownCenter function to use the other kind path creation
	
	PlaceTownCenter();
	
	PlaceTemple();
	
	PlaceAroundTC(ET_VILLAGER, WI_NUM_OF_VILLAGERS, TC1);
	PlaceAroundTC(ET_VILLAGER, WI_NUM_OF_VILLAGERS, TC2);
	PlaceAroundTC(ET_COW, WI_NUM_OF_COWS, TC1);
	PlaceAroundTC(ET_COW, WI_NUM_OF_COWS, TC2);

	PlaceWildBeasts(WI_DEER_MIN, WI_DEER_MAX, WI_DEER_CTD, ET_DEER);
	PlaceWildBeasts(WI_WOLVES_MIN, WI_WOLVES_MAX, WI_WOLVES_CTD, ET_WOLF);
	PlaceWildBeasts(WI_OGRES_MIN, WI_OGRES_MAX, WI_OGRES_CTD, ET_OGRE);
}

void WorldGeneration::PrintMap()
{
	int temp_count = 0;
	for(int outerIndex = 0; outerIndex < world_positions.size(); outerIndex++)
	{
		for(int innerIndex = 0; innerIndex < world_positions.size(); innerIndex++)
		{
			int et_type = world_positions[outerIndex][innerIndex];
			cout << et_type;
			temp_count = temp_count+1;
			if (temp_count % world_info[WI_MAP_SIZE] == 0)
				cout<<endl;
		}
	}
}

void WorldGeneration::PlaceResource(int min, int max, EntityType type)
{
	int temp_random_variable;
	int num_of_resource = 0;

	for(int outerIndex = 0; outerIndex < world_positions.size(); outerIndex++)
	{
		for (int innerIndex = 0; innerIndex < world_positions.size(); innerIndex++)
		{
			temp_random_variable = rand() % 100;
			if (temp_random_variable > world_info[min] && temp_random_variable < world_info[max])
			{
				world_positions[outerIndex][innerIndex] = type;
				num_of_resource++;
				entityCount++;
			}
		}
	}
	//cout<<"number of type "<<type<<":"<<num_of_resource<<endl;
}

void WorldGeneration::PlaceTownCenter()
{
	int TC_placer_count = 0;
	bool keep_going = true;

	while(keep_going)
	{
		TC_placer_count++;
		TC1.set(
			rand() % world_info[WI_MAP_SIZE],	//x-coord
			rand() % world_info[WI_MAP_SIZE]	//y-coord
		);
		TC2.set(
			rand() % world_info[WI_MAP_SIZE],	//x-coord
			rand() % world_info[WI_MAP_SIZE]	//y-coord
		);

		if(TC1.distance(TC2) > world_info[WI_MAP_SIZE]/2)
			keep_going=false;
	}

	//placePaths2(TC1);//uncomment these to use the second(inferior) path creation
	//placePaths2(TC2);

	/**************************/
	/***move away from edges***/
	/**************************/
	shiftFromEdge(TC1);
	shiftFromEdge(TC2);
	/**********************/
	/***clear TCs' area***/
	/**********************/
	clearArea(TC1);
	clearArea(TC2);
	/**************************/
	/***set locations of TCs***/
	/**************************/
	world_positions[TC1.getY()][TC1.getX()] = ET_TOWN_CENTER;// team 1
	entityCount++;
	world_positions[TC2.getY()][TC2.getX()] = ET_TOWN_CENTER;// team 2
	entityCount++;
}

void WorldGeneration::PlaceTemple()
{
	/******************/
	/***find offsets***/
	/******************/

	int x_offset1 = findOffset(3);
	int y_offset1 = findOffset(3);
	int x_offset2 = findOffset(3);
	int y_offset2 = findOffset(3);
	/**********************************/
	/***use offsets to place temples***/
	/**********************************/
	world_positions[ TC1.getY() + y_offset1 ][ TC1.getX() + x_offset1 ] = ET_TEMPLE;//team 1
	entityCount++;
	world_positions[ TC2.getY() + y_offset2 ][ TC2.getX() + x_offset2 ] = ET_TEMPLE;//team 2
	entityCount++;
}

void WorldGeneration::PlaceAroundTC(EntityType type, int num_of_entities, Position pos)
{
	int number = 0;
	int team_type_count = 0;
	Position here;

	int pos_x = pos.getX();
	int pos_y = pos.getY();

	while (team_type_count < world_info[num_of_entities])
	{
		for (int outerIndex = pos_y - 4; outerIndex <= pos_y + 4; outerIndex++)
		{
			for (int innerIndex = pos_x - 6; innerIndex < pos_x + 6; innerIndex++)
			{
				here.set(innerIndex, outerIndex);
				int chance_for_beast = rand() % 100;
				if (world_positions[outerIndex][innerIndex] == ET_NONE && team_type_count < world_info[num_of_entities] && chance_for_beast < 20 && here.distance(pos) > 5)
				{
					world_positions[outerIndex][innerIndex] = type;
					team_type_count++;
					entityCount++;
					number++;
				}
				else if (team_type_count == world_info[num_of_entities])
					break;
			}
		}
	}
	//cout << "number of type " << type << ": " << number << " around position: (" << pos.getX() << ", " << pos.getY() << ")" << endl;
}

void WorldGeneration::PlaceWildBeasts(int min, int max, int delete_chance, EntityType type)
{
	Position here;
	for(int outerIndex = 0; outerIndex < world_positions.size(); outerIndex++)
	{
		for(int innerIndex = 0; innerIndex < world_positions.size(); innerIndex++)
		{
			int chance_for_entity = rand() % 100;
			if (world_positions[outerIndex][innerIndex] == ET_NONE && chance_for_entity >= world_info[min] && chance_for_entity < world_info[max])
			{
				world_positions[outerIndex][innerIndex] = type;
				entityCount++;

				here.set(innerIndex, outerIndex);

				int chance_to_delete = rand() % 100;

				if (TC1.distance(here) <= 30.0 || TC2.distance(here) <= 30.0 || chance_to_delete <= world_info[delete_chance])
				{
					world_positions[outerIndex][innerIndex] = ET_NONE;
					entityCount--;
				}
			}
		}
	}
}

EntityReference WorldGeneration::getNextEntity()
{
	double length_to_tc1;
	double length_to_tc2;
	EntityReference to_return = new Entity(current);
	do
	{
		if(world_positions[current.getY()][current.getX()]==ET_NONE)
		{
			if(cycled == true)
			{
				return to_return;
			}
			else
			{
				nextPosition();
			}
		}
		else
		{
			if(cycled == true)
			{
				return to_return;
			}
			else
			{
			to_return->setEntityType(world_positions[current.getY()][current.getX()]);//set the entity's type which is stored in world_positions[][]
			to_return->setPosition(current);//the the entity's position

			switch(world_positions[current.getY()][current.getX()])//switch to set faction of the returned entity
			{
				//resources
				case ET_TREE:
				case ET_STONE:
				case ET_IRON:
					to_return->setFaction(F_RESOURCE);
					to_return->setGroup(EG_RESOURCE);
					break;
				//passive animals
				case ET_DEER:
					to_return->setFaction(F_ANIMAL_PASSIVE);
					to_return->setGroup(EG_PASSIVE);
					break;
				//hostile animals
				case ET_WOLF:
				case ET_OGRE:
					to_return->setFaction(F_ANIMAL_HOSTILE);
					to_return->setGroup(EG_HOSTILE);
					break;
				//domestic animals
				case ET_COW:
					to_return->setFaction(F_ANIMAL_DOMESTIC);
					to_return->setGroup(EG_DOMESTIC);
					break;
				//everything whose faction is not determined by what it is
				default:
					length_to_tc1 = TC1.distance(current);
					length_to_tc2 = TC2.distance(current);
					if(length_to_tc1<length_to_tc2)
						to_return->setFaction(F_PLAYER_1);
					else
						to_return->setFaction(F_PLAYER_2);

					if(world_positions[current.getY()][current.getX()] == ET_VILLAGER)
						to_return->setGroup(EG_VILLAGER);
					else
						to_return->setGroup(EG_BUILDING);


					break;
			}

			nextPosition();
			return to_return;
			}
		}
	}while(true);

}

int WorldGeneration::getEntityCount()
{
	return entityCount;
}

void WorldGeneration::nextPosition()
{
	int prev_x = current.getX();
	int prev_y = current.getY();
	current.move(D_RIGHT);
	if(current.getX() == prev_x)
	{
		current.set(0,prev_y);
		current.move(D_DOWN);
		if(current.getY() == prev_y)
		{
			current.set(0,0);
			cycled = true;
		}
	}
}

int WorldGeneration::findOffset(int dis)
{
	int x = rand()%100;
	if(x > 50)
		return 0-dis;
	else
		return dis;

}

int WorldGeneration::shiftFromEdge(int coord)
{
	if(coord-9 < 0)
		return coord += 18;
	else if(coord+9 > world_info[WI_MAP_SIZE]-1)
		return coord -= 18;
	else return coord;
}


void WorldGeneration::shiftFromEdge(Position & position)
{
	position.set(
		shiftFromEdge(position.getX()),
		shiftFromEdge(position.getY())
	);
}

void WorldGeneration::clearArea(Position pos)
{
	Position here;
	int pos_x = pos.getX();
	int pos_y = pos.getY();

	for(int outerIndex = pos_y-9; outerIndex < pos_y+9; outerIndex++)
	{
		for(int innerIndex = pos_x-9; innerIndex < pos_x+9; innerIndex++)
		{
			here.set(innerIndex, outerIndex);
			if(world_positions[outerIndex][innerIndex] == ET_TOWN_CENTER)
				;//do nothing
			else if(here.distance(pos) < 8)
			{
				if(world_positions[outerIndex][innerIndex] != ET_NONE)
					entityCount--;
				world_positions[outerIndex][innerIndex] = ET_NONE;
			}
		}
	}
}

void WorldGeneration::createPath(int seed)
{
	Position path_end;
	Position path_start;
	int loc = seed % 2;

	path_start = findPathStart(loc);
	path_end.set(path_start.getX() + 1, path_start.getY() + 1);
	world_positions[path_end.getY()][path_end.getX()] = ET_NONE;

	//cout << "path starts at (" << path_start.getX() << ", " << path_start.getY() << ")" << endl;
	//cout << "path at (" << path_end.getX() << ", " << path_end.getY() << ")" << endl;
	while (path_end.getX() + 1 <= world_info[WI_MAP_SIZE] - 1 && path_end.getY() + 1 <= world_info[WI_MAP_SIZE] - 1)
	{
		int x_offset = findOffset(1);
		int y_offset = findOffset(1);

		if (path_end.getX() == world_info[WI_MAP_SIZE] / 2 || path_end.getY() == world_info[WI_MAP_SIZE] / 2
			|| path_end.getX() == world_info[WI_MAP_SIZE] / 3 || path_end.getY() == world_info[WI_MAP_SIZE] / 3
			|| path_end.getX() == world_info[WI_MAP_SIZE] / 4 || path_end.getY() == world_info[WI_MAP_SIZE] / 4)
		
			loc = pathChange(loc);
		
		if (loc == 0)//even: starts on x-axis
		{
			path_end.set(path_end.getX()+x_offset, path_end.getY() + 1);
			//cout << "path at "<<path_end<< endl;
			world_positions[path_end.getY()][path_end.getX()] = ET_NONE;
			if (x_offset < 1 && path_end.getY() < world_info[WI_MAP_SIZE]-1)
				world_positions[path_end.getY() + 1][path_end.getX()] = ET_NONE;
			else
				world_positions[path_end.getY() - 1][path_end.getX()] = ET_NONE;
		}
		else//odd: starts on y-axis
		{
			path_end.set(path_end.getX() + 1, path_end.getY()+y_offset);
			world_positions[path_end.getY()][path_end.getX()] = ET_NONE;
			if (y_offset < 1 && path_end.getX() < world_info[WI_MAP_SIZE]-1)
				world_positions[path_end.getY()][path_end.getX() + 1] = ET_NONE;
			else
				world_positions[path_end.getY()][path_end.getX() - 1] = ET_NONE;
		}

	}
	//cout << "path ends at (" << path_end.getX() << ", " << path_end.getY() << ")" << endl;
}

Position WorldGeneration::findPathStart(int loc)
{
	bool keep_going = true;
	Position path_start;

	while (keep_going)
	{
		int spot = rand() % world_info[WI_MAP_SIZE];
		if (spot > 10 && spot < world_info[WI_MAP_SIZE] - 10)
		{
			if (loc == 0)//even: starts on x-axis
				path_start.set(spot, 0);
			else//odd: starts on y-axis
				path_start.set(0, spot);
			keep_going = false;
			world_positions[path_start.getY()][path_start.getX()] = ET_NONE;
		}
	}
	return path_start;
}

int WorldGeneration::pathChange(int loc)
{
	// This function can be optimized away to just "loc = 1 - loc;" in place of the function call. -CH
	int x = rand() % 2;
	if (x == 0 && loc == 0) return 1;
	if (x == 0 && loc == 1) return 0;
	if (x == 1 && loc == 0) return 1;
	if (x == 1 && loc == 1) return 0;
	return 0;
}

void WorldGeneration::placePaths()
{
	for (int i = 0; i <= world_info[WI_MAP_SIZE] / 10; i++)
	{
		createPath(rand());
	}
}

void WorldGeneration::placePaths2(Position team)
{
	for (int x = 0; x < 8; x++)
	{
		Direction move;
		Direction move2;
		switch(x)
		{
			default:
			case 0: move = D_UP;    move2 = D_UP;    break;
			case 1: move = D_UP;    move2 = D_LEFT;  break;
			case 2: move = D_LEFT;  move2 = D_LEFT;  break;
			case 3: move = D_DOWN;  move2 = D_LEFT;  break;
			case 4: move = D_DOWN;  move2 = D_DOWN;  break;
			case 5: move = D_DOWN;  move2 = D_RIGHT; break;
			case 6: move = D_RIGHT; move2 = D_RIGHT; break;
			case 7: move = D_UP;    move2 = D_RIGHT; break;
		}

		Position path = team;
		int path_depth = 0;

		while (path.getX() + 1 <= world_info[WI_MAP_SIZE] - 1 && path.getY() + 1 <= world_info[WI_MAP_SIZE] - 1
			&& path.getX() - 1 >= 1 && path.getY() - 1 >= 1)
		{
			int x_offset = findOffset(1);
			int y_offset = findOffset(1);

			if (move == move2)
			{
				path.move(move);
				world_positions[path.getY()][path.getX()] = ET_NONE;
				path.set(path.getX() + x_offset, path.getY());
				world_positions[path.getY()][path.getX()] = ET_NONE;
				path.set(path.getX(), path.getY() + y_offset);
				world_positions[path.getY()][path.getX()] = ET_NONE;
			}
			else
			{
				path.move(move);
				int rands = rand() % 2;
				if (rands == 0) path.set(path.getX(), path.getY() + y_offset);
				else path.set(path.getX() + x_offset, path.getY());
				world_positions[path.getY()][path.getX()] = ET_NONE;
				path.move(move2);
				world_positions[path.getY()][path.getX()] = ET_NONE;
			}
			path_depth++;
			int rands2 = rand() % 18;
			if (path_depth > world_info[WI_MAP_SIZE] / 2)
			{
				if (rands2 == 0) break;
			}
		}
	}
}

Position WorldGeneration::getTC1()
{
	return TC1;
}

Position WorldGeneration::getTC2()
{
	return TC2;
}

int WorldGeneration::getWorldSize()
{
	return world_info[WI_MAP_SIZE];
}

bool WorldGeneration::setProperty(string property, int value)
{
	if (property == "seed")
	{
		if (value >= 0)
			world_info[WI_SEED] = value;
		else
			world_info[WI_SEED] = time(0);
		return true;
	}
	else if (property == "map_size")
	{
		world_info[WI_MAP_SIZE] = value;
		return true;
	}
	else if (property == "difficulty")
	{
		world_info[WI_DIFFICULTY] = value;
		return true;
	}
	else if (property == "num_of_villagers")
	{
		world_info[WI_NUM_OF_VILLAGERS] = value;
		return true;
	}
	else if (property == "num_of_cows")
	{
		world_info[WI_NUM_OF_COWS] = value;
		return true;
	}
	else if (property == "trees_min")
	{
		world_info[WI_TREES_MIN] = value;
		return true;
	}
	else if (property == "trees_max")
	{
		world_info[WI_TREES_MAX] = value;
		return true;
	}
	else if (property == "iron_min")
	{
		world_info[WI_IRON_MIN] = value;
		return true;
	}
	else if (property == "iron_max")
	{
		world_info[WI_IRON_MAX] = value;
		return true;
	}
	else if (property == "stone_min")
	{
		world_info[WI_STONE_MIN] = value;
		return true;
	}
	else if (property == "stone_max")
	{
		world_info[WI_STONE_MAX] = value;
		return true;
	}
	else if (property == "deer_min")
	{
		world_info[WI_DEER_MIN] = value;
		return true;
	}
	else if (property == "deer_max")
	{
		world_info[WI_DEER_MAX] = value;
		return true;
	}
	else if (property == "deer_chance_to_delete")
	{
		world_info[WI_DEER_CTD] = value;
		return true;
	}
	else if (property == "wolves_min")
	{
		world_info[WI_WOLVES_MIN] = value;
		return true;
	}
	else if (property == "wolves_max")
	{
		world_info[WI_WOLVES_MAX] = value;
		return true;
	}
	else if (property == "wolves_chance_to_delete")
	{
		world_info[WI_WOLVES_CTD] = value;
		return true;
	}
	else if (property == "ogres_min")
	{
		world_info[WI_OGRES_MIN] = value;
		return true;
	}
	else if (property == "ogres_max")
	{
		world_info[WI_OGRES_MAX] = value;
		return true;
	}
	else if (property == "ogres_chance_to_delete")
	{
		world_info[WI_OGRES_CTD] = value;
		return true;
	}
	else return false;
}
