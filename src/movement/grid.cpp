/*
template <typename T>
Grid::Grid<T>(int size) :
	size(size)
{
	grid = new T*[size];
	for(int y = 0; y < size; y ++)
	{
		grid[y] = new T[size];
		for(int x = 0; x < size; x ++)
			grid[y][x] = 0;
	}
}

template <typename T>
void Grid<T>::set(Position position, T value)
{
	int x = position.getX();
	int y = position.getY();

	if (x >= 0 && x < size && y >= 0 && y < size)
		grid[y][x] = value;
}

template <typename T>
T Grid<T>::get(Position position)
{
	int x = position.getX();
	int y = position.getY();

	return grid[y][x];
}

template <typename T>
T& Grid<T>::operator[] (Position pos)
{
	return grid[pos.getY()][pos.getX()];
}
*/