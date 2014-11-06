#ifndef ENTITY_MOBILE_H_
#define ENTITY_MOBILE_H_

#include "entity.h"

class MobileEntity : public Entity
{
private:
	int hunger;
	int strength;
	int defense;

	TaskReference task;
	Entity * target;
public:
	MobileEntity(const Entity&);
	int getHunger();
	int getStrength();
	int getDefense();
	void setHunger(int);
	void setStrength(int);
	void setDefense(int);

	void update(ObstructionMapReference obstructionMap);

	bool hasTask();
	void setTask(TaskReference);
};

#endif