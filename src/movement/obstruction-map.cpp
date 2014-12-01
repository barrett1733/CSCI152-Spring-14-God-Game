//
//  File: obstruction-map.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Obstruction Map Class Implementation
//

#include "obstruction-map.h"

ObstructionMap::ObstructionMap(int size) :
	size(size)
{
	occupied = new ObstructionType*[size];
	for(int y = 0; y < size; y ++)
	{
		occupied[y] = new ObstructionType[size];
		for(int x = 0; x < size; x ++)
			occupied[y][x] = OT_EMPTY;
	}
}

void ObstructionMap::set(Position position, ObstructionType value)
{
	int x = position.getX();
	int y = position.getY();

	if(x >= 0 && x < size && y >= 0 && y < size)
		occupied[y][x] = value;
}


bool ObstructionMap::isObstructed(Position position)
{
	int x = position.getX();
	int y = position.getY();

	if (x >= 0 && x < size && y >= 0 && y < size)
		return occupied[y][x] == OT_OBSTRUCTED;

	return false;
}

bool ObstructionMap::isConsidered(Position position)
{
	int x = position.getX();
	int y = position.getY();

	if (x >= 0 && x < size && y >= 0 && y < size)
		return occupied[y][x] == OT_CONSIDERED;

	return false;
}


bool ObstructionMap::isOpen(Position position)
{
	int x = position.getX();
	int y = position.getY();

	if(x >= 0 && x < size && y >= 0 && y < size)
		return occupied[y][x] == OT_EMPTY;

	return false;
}

Position ObstructionMap::findOpenPosition(Position origin)
{/*
	Position position = origin;
	Direction direction = D_NORTH;
	int rangeLimit = 1;
	int range = 0;

	while(rangeLimit < 20)
	{
		for(range = 0; range < rangeLimit; range ++)
		{
			position.move(direction);
			position.move(direction);

			if(isOpen(position) && rand()%8==0)
				return position;
		}

		switch(direction)
		{
			case D_NORTH:  direction = D_EAST;   break;
			case D_SOUTH:  direction = D_WEST;   break;
			case D_EAST:   direction = D_SOUTH;  rangeLimit ++;   break;
			case D_WEST:   direction = D_NORTH;  rangeLimit ++;   break;
		}
	}


	return origin;
	*/
	Position position = origin;
	Direction directionArray[D_COUNT - D_NORTH];
	int amtDirections = 0;
	for (int i = 0; i < D_COUNT - D_NORTH; i++)
		directionArray[i] = 0;
	for (int i = D_NORTH; i < D_COUNT; i++)
	{
		Position newpos = origin;
		newpos.moveUnchecked(i);
		if (isOpen(newpos))
		{
			directionArray[amtDirections] = i;
			amtDirections++;
		}
	}
	if (amtDirections > 0)
		position.move(directionArray[rand() % amtDirections]);
	return position;
	
}
