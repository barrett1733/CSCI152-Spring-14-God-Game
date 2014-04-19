
#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>
#include <map>

#include "sdl/sdl-entity.h"
#include "sdl/sdl-map-view.h"
#include "entity.h"
#include "config.h"

typedef std::map<EntityType, int> Entity_HealthMap;
typedef std::pair<EntityType, int> Entity_HealthPair;

/*
Entity Data list, this is what I have.
	storing in map
	entityType	<->	health

	"nearly" constructed entity passed
	eg. a full entity except for a health.
*/
struct EntityRecord
{
	Entity * entity;
	SdlEntityReference widget;

	void update()
	{
		if(entity) entity->update();
		if(widget) widget->update();
	}
};

class EntityManager : public Config
{
	bool visible;

	std::vector<WidgetReference> widgetList;
	std::vector<EntityRecord*> recordList;

	std::map<Faction, std::vector<EntityRecord*> > factionMap;
	// these lists are sub-catagories of the entitylist, should still be the same reference //
	std::vector<EntityRecord*> villagerList;
	std::vector<EntityRecord*> peacefulMobList;
	std::vector<EntityRecord*> enemyList;
	std::vector<EntityRecord*> buildingList;

	// data to pair up Entity Type and Health
	std::map<EntityType, int> Entity_HealthMap;


	SdlMapView mapView;
	int worldSize;

public:
	EntityManager(int worldSize);

	EntityRecord * createRecord(const EntityReference);
	EntityRecord * createRecord(const Entity&);
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
