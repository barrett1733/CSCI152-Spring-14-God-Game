#include "distance.h"

double ManhattanDistance(Position node, Position goal)
{
	double dx = abs(node.getX() - goal.getX());
	double dy = abs(node.getY() - goal.getY());
	return dx + dy;
}

double DiagonalDistance(Position node, Position goal)
{
	double dx = abs(node.getX() - goal.getX());
	double dy = abs(node.getY() - goal.getY());
	return std::max(dx, dy);
}

double EuclideanDistance(Position node, Position goal)
{
	double dx = abs(node.getX() - goal.getX());
	double dy = abs(node.getY() - goal.getY());
	return sqrt(dx * dx + dy * dy);
}
