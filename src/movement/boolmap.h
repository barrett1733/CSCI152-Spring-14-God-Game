#ifndef BOOLMAP_H_
#define BOOLMAP_H_

#include "position.h"

class BoolMap
{
	bool** boolmap;
	int size_x, size_y;

public:
	BoolMap(int size_x, int size_y);
	~BoolMap();
	void clear();
	bool& operator[] (Position);
};

#endif