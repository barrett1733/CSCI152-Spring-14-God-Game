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

#include "entity.h"
#include <vector>

class Creature
{
	std::vector<MobileEntityReference> creatureList; // list of creatures

public:
	Creature();
	void importEntity(EntityReference);
	void decideAction(MobileEntityReference);
	void wander(MobileEntityReference);
	void attack();
	void flee();
	MobileEntityReference getACreature();
	void update();
};

typedef Creature * CreatureReference;

#endif