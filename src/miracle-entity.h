/*
 *  Miracle Entity is a static entity that preforms actions
 * on nearby entitites.
 * needs a constructor
 * has an update function.
*/
#include "entity.cpp"

class miracle-entity:public entity{
public:
	// has from entity
	// EntityType
	// health
	// position
	miracle-entity(EntityType, int health, Position, Faction);
	miracle-entity(const Entity&);
	void update(std::vector<Entity*>& entityList, ObstructionMapReference obstructionMap);
}