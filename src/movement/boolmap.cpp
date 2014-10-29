#include "boolmap.h"

BoolMap::BoolMap(int size) : size(size)
{
	boolmap = new bool*[size];
	for (int i = 0; i < size; i++)
	{
		boolmap[i] = new bool[size];
		for (int j = 0; j < size; j++)
			boolmap[i][j] = false;
	}
}

BoolMap::~BoolMap()
{
	for (int i = 0; i < size; i++)
	{
		delete[] boolmap[i];
		boolmap[i] = NULL;
	}
	delete[] boolmap;
	boolmap = NULL;
}

void BoolMap::clear()
{
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	{
		boolmap[i][j] = false;
	}
}

bool& BoolMap::operator[] (Position pos)
{
	return boolmap[pos.getX()][pos.getY()];
}
