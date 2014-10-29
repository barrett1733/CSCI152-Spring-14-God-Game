#ifndef BOOLMAP_H_
#define BOOLMAP_H_

#include "position.h"

class BoolMap
{
	bool** boolmap;
	int size;

public:
	BoolMap(int size);
	~BoolMap();
	void clear();
	bool& operator[] (Position);
};

#endif