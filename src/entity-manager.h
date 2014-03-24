
#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>
#include <map>

#include "sdl/sdl-entity.h"
#include "entity.h"

typedef std::map<EntityType, std::int> Entity_HealthMap;
typedef std::pair<EntityType, std::int> Entity_HealthPair;

/*
Entity Data list, this is what I have.
	storing in map
	entityType	<->	health
	
	"nearly" constructed entity passed
	eg. a full entity except for a health.

*/
struct EM_Record
{
	EM_Record(Entity* in){
		this->entity=in;
		
		this->entity->setMaxHealth(100); // MAGIC
		this->entity->setCurrentHealth(100); // these will be changed once the list is completed
		
		this->widget=new SdlEntity();
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
