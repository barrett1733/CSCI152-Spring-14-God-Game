
#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>
#include <map>

#include "config.h"
#include "entity.h"
#include "village-manager.h"
#include "sdl/sdl-entity.h"
#include "sdl/sdl-map-view.h"
#include "sdl/sdl-widget-container.h"
#include "obstruction-map.h"

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

	void update(std::vector<EntityReference>& entityList, ObstructionMapReference obstructionMap)
	{
		if(entity) entity->update(entityList, obstructionMap);
		if(widget) widget->update();
	}
};

class EntityManager : public Config
{
	bool visible;

	std::vector<EntityRecord*> recordList;
	std::vector<EntityReference> entityList;
	std::vector<WidgetReference> widgetList;

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

	ObstructionMapReference obstructionMap;

	static EntityManager * self;
	static VillageManager villageManager;
	static bool callbackMapInitialized;
	static std::map<std::string, void (*)(SDL_Event&, WidgetReference)> callbackMap;
	static WidgetContainerReference buttonContainer;

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


	static void initializeCallbackMap();

	static void build(SDL_Event&, WidgetReference);
	static void miracle(SDL_Event&, WidgetReference);

	static void sliderCallback(SDL_Event&, WidgetReference);
	static void triangleSliderCallback(SDL_Event&, WidgetReference);
	// From Config, we use this to pull from a config file
	// bool setProperty(std::string property, std::string value);
	// bool setProperty(std::string property, int value);
	// bool setProperty(std::string property, int value1, int value2);
};

#endif
