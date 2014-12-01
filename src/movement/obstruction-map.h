//
//  File: obstruction-map.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Obstruction Map Class Definition
// Stores a 2D array indicating which tiles are obstructed by resources or buildings.
// Provides a method for finding an open space to place something.
//

#ifndef OBSTRUCTION_MAP_H_
#define OBSTRUCTION_MAP_H_

#include "position.h"

enum ObstructionType
{
	OT_EMPTY,
	OT_OBSTRUCTED,
	OT_CONSIDERED
};

class ObstructionMap
{
	int size;
	ObstructionType ** occupied;

public:
	ObstructionMap(int size);

	void set(Position, ObstructionType);
	bool isObstructed(Position);
	bool isConsidered(Position);
	bool isOpen(Position);

	Position findOpenPosition(Position origin);

	friend std::ostream& operator<<(std::ostream & os, const ObstructionMap & map)
	{
		for(int y = 0; y < map.size; y ++)
		{
			for(int x = 0; x < map.size; x ++)
				os << map.occupied[y][x];//(map.occupied[y][x] == OT_EMPTY ? 0 : 1);
			os << std::endl;
		}
		return os;
	}
};

#endif

typedef ObstructionMap * ObstructionMapReference;
