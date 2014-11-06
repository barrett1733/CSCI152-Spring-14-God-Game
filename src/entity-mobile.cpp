#include "entity-mobile.h"

MobileEntity::MobileEntity(const Entity & entity) :
Entity(entity),
task(0),
target(0)
{}

int MobileEntity::getHunger() {
	return this->hunger;
}
int MobileEntity::getStrength() {
	return this->strength;
}
int MobileEntity::getDefense() {
	return this->defense;
}

void MobileEntity::setHunger(int hunger) {
	this->hunger = hunger;
}
void MobileEntity::setStrength(int strength) {
	this->strength = strength;
}
void MobileEntity::setDefense(int defense) {
	this->defense = defense;
}

bool MobileEntity::hasTask()
{
	return task ? true : false;
}

void MobileEntity::setTask(TaskReference task)
{
	if (task)
	{
		this->task = task;
		this->target = task->getTarget();
	}
	else
	{
		this->task = 0;
		this->target = 0;
		// worship or wander?
	}
}

void MobileEntity::update(ObstructionMapReference obstructionMap)
{/*
 Pathfinding test;
 PositionList* toMove;
 toMove = test.findPath(Position(0, 0), this->getPosition(), obstructionMap);
 if (!toMove->empty())
 this->setPosition(toMove->at(0));

 if(target)
 {
 Direction direction = D_NONE;
 int targetX = target->getPosition().getX();
 int targetY = target->getPosition().getY();
 int sourceX = position.getX();
 int sourceY = position.getY();

 if(targetX < sourceX)
 direction |= D_LEFT;
 else if(targetX > sourceX)
 direction |= D_RIGHT;

 if(targetY < sourceY)
 direction |= D_UP;
 else if(targetY > sourceY)
 direction |= D_DOWN;

 if(direction == D_NONE && task)
 ;//task->work();

 // TODO: if(!canMove(direction)) adjust(direction);
 //

 position.move(direction);
 }
 else
 {
 int r = rand();
 switch(r % 4)
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
 }*/
}
