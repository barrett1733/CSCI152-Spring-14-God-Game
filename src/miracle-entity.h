//
//  File: miracle-entity.h
//  Author: Allen Mills
//  CSci 152
//  Spring 2014
//
// Definition for MiracleEntity, a child class of Entity specifically made for Miracles.
// 	A Miracle Entity is a static entity that preforms actions on nearby entitites.
//	Includes a function 'getEntitiesWithin' that will take in a vector of entities, a Postion, and range
//	to return another vector of entites with a sublist of entities within range
//

#ifndef MIRACLE_ENTITY_H_
#define  MIRACLE_ENTITY_H_

#include <vector>
#include "entity.h"

class MiracleEntity:public Entity{
public:
	// has from entity
	// EntityType
	// health
	// position
	MiracleEntity(EntityType, int health, Position, Faction);
	//MiracleEntity(const Entity&);
	void update(std::vector<Entity*>& entityList, ObstructionMapReference obstructionMap);
};

std::vector<Entity*> getEntitiesWithin(double range, Position p, std::vector<Entity*>& entityList);

#endif

