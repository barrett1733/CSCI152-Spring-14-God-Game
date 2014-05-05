/*
 *  Miracle Entity is a static entity that preforms actions
 *  on nearby entitites.
*/
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

