//
//  File: position.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Position Class Implementation
//

#include "position.h"
#include <iostream>

int Position::max_x = 0;
int Position::max_y = 0;

Position::Position() :
	x(0),
	y(0)
{ }

Position::Position(int x, int y) :
	x(x),
	y(y)
{
	//forceSanity();
}

Position::Position(const Position & position) :
	x(position.x),
	y(position.y)
{
	//forceSanity();
}

bool Position::checkSanity(int x, int y)
{
	if (x < 0) return false;
	if (y < 0) return false;
	if (max_x && x > max_x) return false;
	if (max_y && y > max_y) return false;
	return true;
}
//Return true if inside of map
bool Position::checkSanity()
{
	return checkSanity(x, y);
}

void Position::forceSanity()
{
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (max_x && x > max_x) x = max_x;
	if (max_y && y > max_y) y = max_y;
}

Position& Position::operator= (const Position & position)
{
	x = position.x;
	y = position.y;

	//forceSanity();

	return *this;
}

bool Position::set(int x, int y)
{
	if (checkSanity(x, y))
	{
		this->x = x;
		this->y = y;
		return true;
	}
	else
		return false;
}
bool Position::set(Position pos)
{
	return set(pos.x, pos.y);
}
bool Position::setX(int x)
{
	return set(x, y);
}
bool Position::setY(int y)
{
	return set(x, y);
}


int Position::getX()
{
	return x;
}

int Position::getY()
{
	return y;
}

double Position::distance(const Position & position)
{
	int a = x - position.x;
	int b = y - position.y;
	return sqrt(a * a + b * b);
}

double Position::direction(const Position & position)
{
	return atan(y/x) + (x < 0 ? 3.14159265359 : 0);
}

void Position::moveUnchecked(Direction direction)
{
	moveUnchecked(direction, 1);
}

void Position::moveUnchecked(Direction direction, int distance)
{
	if (direction < D_NORTH || direction > D_COUNT)
	{
		if (direction & D_UP)    y -= distance;
		if (direction & D_RIGHT) x += distance;
		if (direction & D_DOWN)  y += distance;
		if (direction & D_LEFT)  x -= distance;
	}
	else
	{
		switch (direction)
		{
		case D_NORTH:	y -= distance; break;
		case D_EAST:	x += distance; break;
		case D_SOUTH:	y += distance; break;
		case D_WEST:	x -= distance; break;
		case D_NORTH_EAST: y -= distance; x += distance; break;
		case D_SOUTH_EAST: y += distance; x += distance; break;
		case D_SOUTH_WEST: y += distance; x -= distance; break;
		case D_NORTH_WEST: y -= distance; x -= distance; break;
		}
	}
}
void Position::move(Direction direction)
{
	return move(direction, 1);
}
void Position::move(Direction direction, int distance)
{
	moveUnchecked(direction, distance);
	forceSanity();
}
Position Position::getNeighbor(Direction dir)
{
	Position pos = *this;
	pos.moveUnchecked(dir);
	return pos;
}