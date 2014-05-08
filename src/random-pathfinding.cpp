#include "random-pathfinding.h"

Direction RandomPathfinding::determineDirection(Position source, Position target)
{
	Direction direction = D_NONE;
	int targetX = target.getX();
	int targetY = target.getY();
	int sourceX = source.getX();
	int sourceY = source.getY();

	if (targetX < sourceX)
		direction |= D_LEFT;
	else if (targetX > sourceX)
		direction |= D_RIGHT;

	if (targetY < sourceY)
		direction |= D_UP;
	else if (targetY > sourceY)
		direction |= D_DOWN;

	return direction;
}
Direction RandomPathfinding::randomDirection(Position source)
{

}
Direction RandomPathfinding::invertDirection(Direction source)
{

}
Position RandomPathfinding::moveTowardsTarget(MobileEntityReference me, Position target)
{
	Position position = me->getPosition();
	position.move(determineDirection(position, target));
	return position;
}
Position RandomPathfinding::moveTowardsTarget(MobileEntityReference me, MobileEntityReference target)
{
	return moveTowardsTarget(me, target->getPosition());
}
Position RandomPathfinding::moveAwayFromTarget(MobileEntityReference me, Position target)
{
	Position position = me->getPosition();
	position.move(determineDirection(position, target));
	return position;
}
Position RandomPathfinding::moveAwayFromTarget(MobileEntityReference me, MobileEntityReference target)
{
	return moveTowardsTarget(me, target->getPosition());
}
Position RandomPathfinding::moveRandomly(MobileEntityReference source)
{
	Position position = source->getPosition();
	int r = rand();
	switch (r % 4)
	{
	case 0:
		position.move(D_UP);
		break;

	case 1:
		position.move(D_RIGHT);
		break;

	case 2:
		position.move(D_DOWN);
		break;

	case 3:
		position.move(D_LEFT);
		break;
	}
	return position;
}
