//
//  CSCI 152, Spring 2014, God Game
//

#ifndef POSITION_H_
#define POSITION_H_

#include <math.h>
#include <iostream>

class Position
{
public:
	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}

	const Position& operator= (const Position & position)
	{
		x = position.x;
		y = position.y;

		return *this;
	}

	int x;
	int y;

	double distance(Position & p)
	{
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}

	double direction(Position & p)
	{
		return atan(y/x) + (x < 0 ? 3.14159265359 : 0);
	}


	friend std::ostream& operator<< (std::ostream & os, const Position & position)
	{
		os << "(" << position.x << ", " << position.y << ")";
		return os;
	}
};

#endif
