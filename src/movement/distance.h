#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "position.h"
#include <algorithm>

double ManhattanDistance(Position node, Position goal);
double DiagonalDistance(Position node, Position goal);
double EuclideanDistance(Position node, Position goal);

#endif