#include "boolmap.h"

BoolMap::BoolMap(int size) : size(size)
{
	boolmap = new bool*[size];
	for (int y = 0; y < size; y++)
	{
		boolmap[y] = new bool[size];
		for (int x = 0; x < size; x++)
			boolmap[y][x] = false;
	}
}

BoolMap::~BoolMap()
{
	for (int y = 0; y < size; y++)
	{
		delete[] boolmap[y];
		boolmap[y] = NULL;
	}
	delete[] boolmap;
	boolmap = NULL;
}

void BoolMap::clear()
{
	for (int y = 0; y < size; y++)
	for (int x = 0; x < size; x++)
	{
		boolmap[y][x] = false;
	}
}

bool& BoolMap::operator[] (Position pos)
{
	return boolmap[pos.getY()][pos.getX()];
}
