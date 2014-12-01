#ifndef GRID_H_
#define GRID_H_

#include "position.h"

template <typename T>
class Grid
{
	int size;
	T ** grid;

public:
	Grid(int size) : size(size)
	{
		grid = new T*[size];
		for (int y = 0; y < size; y++)
			grid[y] = new T[size];
	}

	void set(Position position, T value)
	{
		int x = position.getX();
		int y = position.getY();

		if (x >= 0 && x < size && y >= 0 && y < size)
			grid[y][x] = value;
	}

	T get(Position position)
	{
		int x = position.getX();
		int y = position.getY();

		return grid[y][x];
	}

	T& operator[] (Position pos)
	{
		return grid[pos.getY()][pos.getX()];
	}

	friend std::ostream& operator<<(std::ostream & os, const Grid & map)
	{
		for(int y = 0; y < map.size; y ++)
		{
			for(int x = 0; x < map.size; x ++)
				os << map.grid[y][x];
			os << std::endl;
		}
		return os;
	}
};

#endif