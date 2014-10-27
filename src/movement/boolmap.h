#ifndef BOOLMAP_H_
#define BOOLMAP_H_

#include "position.h"

class BoolMap
{
	bool** boolmap;
	int size;

public:
	BoolMap() {};
	BoolMap(int size);
	~BoolMap();
	void setup(int size);
	void clear();
	void destroy();
	bool& operator[] (Position);
};

#endif