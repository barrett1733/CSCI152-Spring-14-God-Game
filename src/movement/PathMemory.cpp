#include "PathMemory.h"


PathMemory::PathMemory() : currentPath(NULL), pathMap(Position::max_x)
{
	pathMemories.reserve(Position::max_x * Position::max_y);
}

PathMemory::~PathMemory()
{
	for (int i = 0; i < pathMemories.size(); i++)
	{
		delete pathMemories.at(i);
	}
}

void PathMemory::shareMemories(PathMemory* enta, PathMemory* entb)
{
	// Needs to be implemented
}

bool PathMemory::goalReached(Position goal)
{
	if (currentPath)
		return currentPath->target == goal;
	return false;
}

PathMemory::Memory* PathMemory::getMemory(Position start, Position target)
{
	if (!pathMemories.empty())
		for (int i = 0; i < pathMemories.size(); i++)
		{
			if (pathMemories.at(i)->start == start && pathMemories.at(i)->target == target)
			{
				return pathMemories.at(i);
			}
			else if (pathMemories.at(i)->start == target && pathMemories.at(i)->target == start)
			{
				switchMemoryDirection(pathMemories.at(i));
				return pathMemories.at(i);
			}
		}
	return NULL;
}

bool PathMemory::existsPath(Position start, Position target)
{
	return getMemory(start, target);
}

void PathMemory::switchMemoryDirection(Memory* memory)
{
	Position temp = memory->start;
	memory->start = memory->target;
	memory->target = temp;
	std::reverse(memory->path.begin(), memory->path.end());
}

void PathMemory::startPath(Position start, Position target)
{
	currentPath = new Memory();
	currentPath->start = start;
	currentPath->target = target;
	currentPath->pathComplete = false;
}

Position PathMemory::getNextPosition(Position pos)
{
	for (int i = 0; i < currentPath->path.size(); i++)
		if (currentPath->path.at(i) == pos && i > 0)
			return currentPath->path[i - 1];
}

Position PathMemory::moveOnPath(Position current, Position next, Position end)
{
	if (!currentPath)
	{
		if (existsPath(current, end))
		{
			currentPath = getMemory(current, end);
		}
		else
		{
			startPath(current, end);
		}
	}
	else
	{
		if (current == end)
			currentPath->pathComplete = true;
		if (currentPath->pathComplete)
		{
			return getNextPosition(current);
		}
		else if (current == next)
		{
			//travel back
		}
		else
		{
			currentPath->path.push_back(current);
			pathMap[current] = VISITED;
			return next;
		}
	}
}
