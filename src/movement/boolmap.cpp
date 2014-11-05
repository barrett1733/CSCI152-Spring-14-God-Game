#include "boolmap.h"

BoolMap::BoolMap(int size_x, int size_y) : size_x(size_x), size_y(size_y)
{
	boolmap = new bool*[size_y];
	for (int y = 0; y < size_y; y++)
	{
		boolmap[y] = new bool[size_x];
		for (int x = 0; x < size_x; x++)
			boolmap[y][x] = false;
	}
}

BoolMap::~BoolMap()
{
	for (int y = 0; y < size_y; y++)
	{
		delete[] boolmap[y];
		boolmap[y] = NULL;
	}
	delete[] boolmap;
	boolmap = NULL;
}

void BoolMap::clear()
{
	for (int y = 0; y < size_y; y++)
		for (int x = 0; x < size_x; x++)
			boolmap[y][x] = false;
}

bool& BoolMap::operator[] (Position pos)
{
	return boolmap[pos.getY()][pos.getX()];
}
