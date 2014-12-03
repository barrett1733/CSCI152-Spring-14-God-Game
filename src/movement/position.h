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
	D_NORTH = 100,
	D_EAST,
	D_SOUTH,
	D_WEST,
	D_NORTH_EAST,
	D_SOUTH_EAST,
	D_NORTH_WEST,
	D_SOUTH_WEST,
	D_COUNT,
};
typedef int Direction;

class Position
{
	int x;
	int y;

	//Creation and moving of a position forces sanity
	//Setting checks sanity
	void forceSanity();
	bool checkSanity(int x, int y);

public:
	Position();
	Position(int x, int y);
	Position(const Position &);

	Position& operator= (const Position &);

	bool checkSanity();

	void moveUnchecked(Direction); // move without forceSanity()
	void moveUnchecked(Direction, int distance);

	void move(Direction);
	void move(Direction, int distance);

	double distance(const Position&);

	Position getNeighbor(Direction);

	bool setX(int x);
	bool setY(int y);
	bool set(int x, int y);
	bool set(Position);
	int getX();
	int getY();

	friend bool operator==(const Position& a, const Position& b)
	{
		if ((a.x == b.x) && (a.y == b.y))
			return true;
		return false;
	}

	friend bool operator<(const Position& a, const Position& b)
	{
		if ((a.x < b.x) && (a.y < b.y))
			return true;
		return false;
	}
	friend bool operator>(const Position& a, const Position& b)
	{
		return !(a < b);
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
