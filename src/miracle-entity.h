/*
 *  Miracle Entity is a static entity that preforms actions
 *  on nearby entitites.
*/
#include <vector>
#include "entity.cpp"

class miracleEntity:public Entity{
public:
	// has from entity
	// EntityType
	// health
	// position
	miracleEntity(EntityType, int health, Position, Faction);
	//miracleEntity(const Entity&);
	void update(std::vector<Entity*>& entityList, ObstructionMapReference obstructionMap);
}

vector<Entity*> getEntitiesWithin(double range, Position p, std::vector<Entity*>& entityList);
