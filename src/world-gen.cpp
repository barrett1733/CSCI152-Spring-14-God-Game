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

WorldGeneration::WorldGeneration(int seed) :
	current(0,0)
{
	//time_t timer;
	srand(seed);//rand must be seeded before placement, if not here then in another module that needs it first
	//if it is used I will remove it from this location

	entityCount = 0;
	cycled = false;

	/*****************
	***get map info***
	*****************/

		ifstream file("res/world-info.txt");
		int n;
		while( file >> n ) world_info.push_back(n);
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

	int mapEdgeLength = world_info[WI_MAP_SIZE];

	world_positions.resize(mapEdgeLength);
	Position::max_x = Position::max_y = mapEdgeLength - 1;

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

	PlaceResource(15, 85, ET_TREE);//trees
	PlaceResource(1, 5, ET_IRON);//iron
	PlaceResource(30, 35, ET_STONE);//stone
	placePaths();
	PlaceTownCenter();
	//createPaths2(TC1);
	//createPaths2(TC2);
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
	int temp_count = 0;
	int sidelength = world_info[WI_MAP_SIZE];
	for(int outerIndex = 0; outerIndex < world_positions.size(); outerIndex++)
	{
		for(int innerIndex = 0; innerIndex < world_positions.size(); innerIndex++)
		{
			int et_type = world_positions[outerIndex][innerIndex];
			cout << et_type;
			temp_count = temp_count+1;
			if(temp_count % sidelength == 0)
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
		for(int innerIndex = 0; innerIndex < world_positions.size(); innerIndex++)
		{
			temp_random_variable = rand() % 100;
			if(temp_random_variable > min && temp_random_variable < max)
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
			rand() % world_info[WI_MAP_SIZE],
			rand() % world_info[WI_MAP_SIZE]	//y-coord
		);

		if(TC1.distance(TC2) > world_info[WI_MAP_SIZE]/2)
			keep_going=false;
	}

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

void WorldGeneration::PlaceVillagers(EntityType type, Position pos)
{
	int team_villager_count = 0;
	Position here;

	int pos_x = pos.getX();
	int pos_y = pos.getY();

	/*********************************************************/
	/***placing villagers around the town center and shrine***/
	/*********************************************************/
	while(team_villager_count < world_info[WI_NUM_OF_VILLAGERS])
	{
		for(int outerIndex = pos_y - 4; outerIndex <= pos_y + 4; outerIndex++)
		{
			for(int innerIndex = pos_x - 6; innerIndex < pos_x + 6; innerIndex++)
			{
				here.set(innerIndex, outerIndex);
				int chance_for_villager = rand() % 100;
				if(world_positions[outerIndex][innerIndex] == ET_NONE && team_villager_count < world_info[WI_NUM_OF_VILLAGERS] && chance_for_villager < 20 && here.distance(pos) > 3)
				{
					world_positions[outerIndex][innerIndex] = type;
					team_villager_count++;
					entityCount++;
				}
				else if(team_villager_count == world_info[WI_NUM_OF_VILLAGERS])
					break;
			}
		}
	}
}

void WorldGeneration::PlaceDomesticBeasts(EntityType type, int num_of_beasts, Position pos)
{
	int team_type_count = 0;
	Position here;

	int pos_x = pos.getX();
	int pos_y = pos.getY();

	while(team_type_count < world_info[num_of_beasts])
	{
		for(int outerIndex = pos_y - 4; outerIndex <= pos_y + 4; outerIndex++)
		{
			for(int innerIndex = pos_x - 6; innerIndex < pos_x + 6; innerIndex++)
			{
				here.set(innerIndex, outerIndex);
				int chance_for_beast = rand() % 100;
				if(world_positions[outerIndex][innerIndex] == ET_NONE && team_type_count < world_info[num_of_beasts] && chance_for_beast < 20 && here.distance(pos) > 5)
				{
					world_positions[outerIndex][innerIndex] = type;
					team_type_count++;
					entityCount++;
				}
				else if(team_type_count == world_info[num_of_beasts])
					break;
			}
		}
	}
}

void WorldGeneration::PlaceWildBeasts(int min, int max, int delete_chance, EntityType type)
{
	for(int outerIndex = 0; outerIndex < world_positions.size(); outerIndex++)
	{
		for(int innerIndex = 0; innerIndex < world_positions.size(); innerIndex++)
		{
			int chance_for_entity = rand() % 100;
			if(world_positions[outerIndex][innerIndex] == ET_NONE && chance_for_entity >= min && chance_for_entity<max)
			{
				world_positions[outerIndex][innerIndex] = type;
				entityCount++;

				Position here;
				here.set(innerIndex, outerIndex);

				int chance_to_delete = rand() % 100;

				if(TC1.distance(here) <= 30.0 || TC2.distance(here) <= 30.0 || chance_to_delete <= delete_chance)
				{
					world_positions[outerIndex][innerIndex] = ET_NONE;
					entityCount--;
				}
			}
		}
	}
}

Entity WorldGeneration::getNextEntity()
{
	//string z="noMoreEntities";
	double length_to_tc1;
	double length_to_tc2;
	Entity to_return(ET_NONE,0,current,FT_NONE);
	do
	{
		if(world_positions[current.getY()][current.getX()]==ET_NONE)
		{
			if(cycled == true)
			{
				return to_return;//throw (1);
			}
			else
			{
				nextPosition();
				//current_moves++;
			}
		}
		else //if(world_positions[current.y][current.x]!=0)
		{
			if(cycled == true)
			{
				return to_return;//throw (1);
			}
			else
			{
			to_return.setEntityType(world_positions[current.getY()][current.getX()]);//set the entity's type
			to_return.setPosition(current);//the the entity's position

			switch(world_positions[current.getY()][current.getX()])
			{
				//resources
				case ET_TREE:
				case ET_STONE:
				case ET_IRON:
					to_return.setFaction(FT_STATIC);
					break;
				//passive animals
				case ET_DEER:
					to_return.setFaction(FT_ANIMAL_PASSIVE);
					break;
				//hostile animals
				case ET_WOLF:
				case ET_OGRE:
					to_return.setFaction(FT_ANIMAL_HOSTILE);
					break;
				//domestic animals
				case ET_COW:
					to_return.setFaction(FT_ANIMAL_DOMESTIC);
					break;
				//everything whose faction is not determined by what it is
				default:
					length_to_tc1 = TC1.distance(current);
					length_to_tc2 = TC2.distance(current);
					if(length_to_tc1<length_to_tc2)
					to_return.setFaction(FT_PLAYER_1);
					else
					to_return.setFaction(FT_PLAYER_2);
					break;
			}

			nextPosition();
			//current_moves++;
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
	current.move(PD_RIGHT);
	if(current.getX() == prev_x)
	{
		current.set(0,prev_y);
		current.move(PD_DOWN);
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

//void WorldGeneration::clearArea(Position pos)
//{
//	for(int outerIndex=pos.y-7; outerIndex < pos.y+7; outerIndex++)
//	{
//		for(int innerIndex=pos.x-7; innerIndex < pos.x+7; innerIndex++)
//		{
//			if(world_positions[outerIndex][innerIndex] == ET_TOWN_CENTER)
//				world_positions[outerIndex][innerIndex] = ET_TOWN_CENTER;
//			else
//			{
//				if(world_positions[outerIndex][innerIndex] != ET_NONE)
//				entityCount--;
//				world_positions[outerIndex][innerIndex] = ET_NONE;
//			}
//		}
//	}
//}

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
				world_positions[outerIndex][innerIndex] = ET_TOWN_CENTER;
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
			//cout << "path at (" << path_end.getX() << ", " << path_end.getY() << ")" << endl;
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
	int x = rand() % 2;
	if (x == 0 && loc == 0) return 1;
	if (x == 0 && loc == 1) return 0;
	if (x == 1 && loc == 0) return 1;
	if (x == 1 && loc == 1) return 0;
}

void WorldGeneration::placePaths()
{
	for (int i = 0; i <= world_info[WI_MAP_SIZE] / 10 ; i++)
	{
		createPath(rand());
	}
}

void WorldGeneration::createPaths2(Position team)
{
	for (int x = 0; x < 8; x++)
	{
		Direction move;
		Direction move2;
		if (x == 0) { move = PD_UP;		move2 = PD_UP; }
		if (x == 1) { move = PD_UP;		move2 = PD_LEFT; }
		if (x == 2) { move = PD_LEFT;	move2 = PD_LEFT; }
		if (x == 3) { move = PD_DOWN;	move2 = PD_LEFT; }
		if (x == 4) { move = PD_DOWN;	move2 = PD_DOWN; }
		if (x == 5) { move = PD_DOWN;	move2 = PD_RIGHT; }
		if (x == 6) { move = PD_RIGHT;	move2 = PD_RIGHT; }
		if (x == 7) { move = PD_UP;		move2 = PD_RIGHT; }

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
				//world_positions[path.getY()][path.getX()] = ET_NONE;
				//world_positions[path.getY()][path.getX()] = ET_NONE;
				path.move(move2);
				world_positions[path.getY()][path.getX()] = ET_NONE;
				//world_positions[path.getY()][path.getX()] = ET_NONE;
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
