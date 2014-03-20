//
//  CSCI 152, Spring 2014, God Game
//

#ifndef POSITION_H_
#define POSITION_H_

#include <math.h>

class Position
{
public:
	int x;
	int y;

	double distance(Position & p)
	{
		return sqrt(x * p.x + y * p.y);
	}

	double direction(Position & p)
	{
		return atan(y/x) + (x < 0 ? 3.14159265359 : 0);
	}
};

#endif
