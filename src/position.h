//
//  CSCI 152, Spring 2014, God Game
//

#ifndef POSITION_H_
#define POSITION_H_

#include <math.h>
#include <iostream>

enum Direction
{
	D_NONE  = 0x00,
	D_UP    = 0x01,
	D_RIGHT = 0x02,
	D_DOWN  = 0x04,
	D_LEFT  = 0x08,
};

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

	void set(int x, int y);
	int getX();
	int getY();

	friend std::ostream& operator<< (std::ostream & os, const Position & position)
	{
		os << "(" << position.x << ", " << position.y << ")";
		return os;
	}

	static int max_x;
	static int max_y;
};

#endif
