
#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>

#include "sdl/sdl-entity.h"
#include "entity.h"

struct EM_Record
{
	EM_Record(Entity* in, COLOR color){
		this->entity=in;
		this->widget=new SdlEntity(color, 16);
		this->widget->enable();
	}
	Entity * entity;
	WidgetReference widget;
};

class EntityManager
{
	std::vector<WidgetReference> widgetList;
	std::vector<EM_Record*> entityList; // list of all current entities on map
	// these lists are sub-catagories of the entitylist, should still be the same reference //
	std::vector<EM_Record*> villagerList;
	std::vector<EM_Record*> peacefulMobList;
	std::vector<EM_Record*> enemyList;
	std::vector<EM_Record*> buildingList;
	
public:
	void createEntity(Entity*);
	void deleteEntity(); // removes entity from all applicable lists
	
	void getEntityType(); 
	// needs a return of some kind, this will define what lists 
	//   the entity is added to or removed from.

	void update();
	void show();
	void hide();
};

#endif
