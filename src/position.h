//
//  File: position.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Position Class Definition
// Maintains an x,y pair corresponding to a position on the map.
// Provides a move() method for adjusting the position via Direction values.
// Enforces boundaries if maximums are set.
//

#ifndef POSITION_H_
#define POSITION_H_

#include <math.h>
#include <iostream>

enum
{
	D_NONE  = 0x00,
	D_UP    = 0x01,
	D_RIGHT = 0x02,
	D_DOWN  = 0x04,
	D_LEFT  = 0x08,
};
enum
{
	D_NORTH    = 0x01,
	D_EAST = 0x02,
	D_SOUTH  = 0x04,
	D_WEST  = 0x08,
};
typedef int Direction;

class Position
{
	int x;
	int y;

	void checkSanity();

public:
	Position();
	Position(int x, int y);
	Position(const Position &);

	Position& operator= (const Position &);

	double distance(const Position &);
	double direction(const Position &);

	void move(Direction);
	void move(Direction, int distance);

	void set(int x, int y);
	int getX();
	int getY();

	friend bool operator==(const Position& a, const Position& b)
	{
		if ((a.x == b.x) && (a.y == b.y))
			return true;
		return false;
	}

	friend bool operator!=(const Position& a, const Position& b)
	{
		return !(a == b);
	}

	friend std::ostream& operator<< (std::ostream & os, const Position & position)
	{
		os << "(" << position.x << ", " << position.y << ")";
		return os;
	}

	static int max_x;
	static int max_y;
};

#endif
