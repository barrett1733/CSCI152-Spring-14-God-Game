
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
	checkSanity();
}

Position::Position(const Position & position) :
	x(position.x),
	y(position.y)
{
	checkSanity();
}

void Position::checkSanity()
{
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(max_x && x > max_x) x = max_x;
	if(max_y && y > max_y) y = max_y;
}

Position& Position::operator= (const Position & position)
{
	x = position.x;
	y = position.y;

	checkSanity();

	return *this;
}

void Position::set(int x, int y)
{
	this->x = x;
	this->y = y;
	checkSanity();
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

void Position::move(Direction dir)
{
	if(dir & D_UP)    y--;
	if(dir & D_RIGHT) x++;
	if(dir & D_DOWN)  y++;
	if(dir & D_LEFT)  x--;

	checkSanity();
}
