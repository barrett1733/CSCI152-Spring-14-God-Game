//
//  File: entity-manager.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Entity Manager Definition
// Implements the Config interface.
// Maintains a list of all game Entities.
// Provides subsets of this list to the Village Manager.
// Maintains the sidebar interface.
//

#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>
#include <map>

#include "config.h"
#include "entity.h"
#include "miracle-entity.h"
#include "village-manager.h"
#include "sdl/sdl-entity.h"
#include "sdl/sdl-map-view.h"
#include "sdl/sdl-widget-container.h"
#include "obstruction-map.h"

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
	std::map<EntityType, int> entityHealthMap;

	SdlMapView * mapView;
	int worldSize;

	ObstructionMapReference obstructionMap;

	static EntityManager * self;
	static VillageManager villageManager;
	static bool callbackMapInitialized;
	static std::map<std::string, void (*)(SDL_Event&, WidgetReference)> callbackMap;
	static WidgetContainerReference buttonContainer;

public:
	EntityManager();
	void setWorldSize(int worldSize);

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
	friend std::ostream & operator<<(std::ostream & os, const EntityManager & manager)
	{
		long entityCount = manager.entityList.size();
		for(long entityIndex = 0; entityIndex < entityCount; entityIndex ++)
		{
			EntityReference entity = manager.entityList[entityIndex];
			os << *entity << std::endl;
		}
		return os;
	}
};

#endif
