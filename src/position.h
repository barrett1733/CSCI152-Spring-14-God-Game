//
//  CSCI 152, Spring 2014, God Game
//

#ifndef POSITION_H_
#define POSITION_H_

#include <math.h>

class Position
{
public:
	double x;
	double y;

	double distance(Position & p)
	{
		int a=abs(x-p.x);
		int b=abs(y-p.y);
		return sqrt(a * a + b * b);
	}

	double direction(Position & p)
	{
		return atan(y/x) + (x < 0 ? 3.14159265359 : 0);
	}
};

#endif
