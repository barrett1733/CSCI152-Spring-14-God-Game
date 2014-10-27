#include "boolmap.h"

BoolMap::BoolMap(int size) : size(size)
{
	setup(size);
}

BoolMap::~BoolMap()
{
	destroy();
}

void BoolMap::setup(int size_)
{
	size = size_;
	boolmap = new bool*[size];
	for (int i = 0; i < size; i++)
	{
		boolmap[i] = new bool[size];
		for (int j = 0; j < size; j++)
			boolmap[i][j] = false;
	}
}

void BoolMap::clear()
{
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	{
		boolmap[i][j] = false;
	}
}

void BoolMap::destroy()
{
	for (int i = 0; i < size; i++)
	{
		delete[] boolmap[i];
		boolmap[i] = NULL;
	}
	delete[] boolmap;
	boolmap = NULL;
}

bool& BoolMap::operator[] (Position pos)
{
	return boolmap[pos.getX()][pos.getY()];
}
