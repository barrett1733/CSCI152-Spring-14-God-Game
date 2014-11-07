//
//  File: creature.h
//  Author: Steven Barrett
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Creature Class Implementation
//
#ifndef CREATURE_H_
#define CREATURE_H_

#include "../entity.h"

class Creature
{

public:
	Creature();
	void decideAction(MobileEntityReference);
	void wander(MobileEntityReference);
	void attack();
	void flee();
	MobileEntityReference getACreature();
	void update();
};

typedef Creature * CreatureReference;

#endif