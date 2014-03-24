
#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>

#include "sdl/sdl-entity.h"
#include "entity.h"

struct EM_Record
{
	Entity * entity;
	WidgetReference widget;
};

class EntityManager
{
	std::vector<WidgetReference> widgetList;
	std::vector<Entity*> entityList; // list of all current entities on map
	// these lists are sub-catagories of the entitylist, should still be the same reference //
	std::vector<Entity*> villagerList;
	std::vector<Entity*> peacefulMobList;
	std::vector<Entity*> enemyList;
	std::vector<Entity*> buildingList;
	
public:
	void createEntity();
	void deleteEntity(); // removes entity from all applicable lists
	
	void getEntityType(); 
	// needs a return of some kind, this will define what lists 
	//   the entity is added to or removed from.

	void update();
	void show();
	void hide();
};

#endif
