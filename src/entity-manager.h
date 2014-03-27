
#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>
#include <map>

#include "sdl/sdl-entity.h"
#include "entity.h"
#include "config.h"

/*
Entity Data list, this is what I have.
	storing in map
	entityType	<->	health

	"nearly" constructed entity passed
	eg. a full entity except for a health.
*/
struct EM_Record
{
	EM_Record(Entity* in, int health){
		this->entity=in;

		this->entity->setMaxHealth(health); // MAGIC
		this->entity->setCurrentHealth(1); // these will be changed once the list is completed

		this->widget=new SdlEntity(); // SDL will eventually need more info.
		this->widget->enable();
	}
	Entity * entity;
	WidgetReference widget;
};

class EntityManager : public Config
{
	std::vector<WidgetReference> widgetList;
	std::vector<EM_Record*> entityList; // list of all current entities on map
	// these lists are sub-catagories of the entitylist, should still be the same reference //
	std::vector<EM_Record*> villagerList;
	std::vector<EM_Record*> peacefulMobList;
	std::vector<EM_Record*> enemyList;
	std::vector<EM_Record*> buildingList;

	// data to pair up Entity Type and Health
	std::map<EntityType, int> Entity_HealthMap;

public:
	void createEntity(Entity*);
	void deleteEntity(); // removes entity from all applicable lists

	void getEntityType();
	// needs a return of some kind, this will define what lists
	//   the entity is added to or removed from.

	void update();
	void show();
	void hide();

	// From Config, we use this to pull from a config file
	bool setProperty(std::string property, std::string value);
	bool setProperty(std::string property, int value);
	bool setProperty(std::string property, int value1, int value2);
};

#endif
