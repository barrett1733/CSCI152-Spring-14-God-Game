#include "PathMemory.h"


PathMemory::PathMemory() : currentPath(NULL), pathMap(Position::max_x+1)
{
	pathMemories.reserve(Position::max_x * Position::max_y);
	for (int i = 0; i < Position::max_x + 1; i++)
		for (int j = 0; j < Position::max_x + 1; j++)
			pathMap[Position(i,j)] = UNKNOWN;
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
	currentPath->path.push_back(start);
	pathMemories.push_back(currentPath);
}

Position PathMemory::getPrevPosition()
{
	if (!currentPath->path.empty())
		return *(currentPath->path.end() - 1);
}

bool PathMemory::onPath()
{
	return currentPath;
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
		{
			currentPath->path.push_back(current);
			currentPath->pathComplete = true;
			currentPath = NULL;
			return current;
		}
		if (currentPath->pathComplete)
		{
			return getPrevPosition();
		}
		else if (pathMap[next] == VISITED)
		{
			pathMap[current] = VISITED;
			if (currentPath->path.size() >= 2)
			{
				Position pos = *(currentPath->path.end() - 1);
				currentPath->path.erase(currentPath->path.end() - 1);
				return pos;
			}
			return currentPath->start;
		}
		else
		{
			currentPath->path.push_back(current);
			pathMap[current] = VISITED;
			return next;
		}
	}
	return next;
}
