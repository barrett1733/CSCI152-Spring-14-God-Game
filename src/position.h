//
//  CSCI 152, Spring 2014, God Game
//

#ifndef POSITION_H_
#define POSITION_H_

#include <math.h>
#include <iostream>

enum Direction
{
	PD_UP    = 0x01,
	PD_RIGHT = 0x02,
	PD_DOWN  = 0x04,
	PD_LEFT  = 0x08,
};

class Position
{

	void checkSanity();

public:
	Position();
	Position(int x, int y);
	Position(const Position &);

	int x;
	int y;
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
