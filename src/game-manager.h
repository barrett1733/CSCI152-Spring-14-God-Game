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

#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <vector>
#include <map>
#include <ctime>

#include "config.h"
#include "entity.h"
#include "miracle-entity.h"
#include "village-manager.h"
#include "sdl/sdl-entity.h"
#include "sdl/sdl-map-view.h"
#include "sdl/sdl-widget-container.h"
#include "obstruction-map.h"
#include "entity-manager.h"


class GameManager : public Config
{
	bool visible;

	// data to pair up Entity Type and Health
	std::map<EntityType, int> entityHealthMap;

	SdlMapView * mapView;
	int worldSize;

	ObstructionMapReference obstructionMap;

	static GameManager * self;
	static VillageManager villageManager;
	static EntityManager entityManager;
	static bool callbackMapInitialized;
	static std::map<std::string, void (*)(SDL_Event&, WidgetReference)> callbackMap;
	static WidgetContainerReference buttonContainer;


public:
	GameManager();
	void setup();
	void update();
	void show();
	void hide();


	static void initializeCallbackMap();

	static void build(SDL_Event&, WidgetReference);
	static void miracle(SDL_Event&, WidgetReference);

	static void sliderCallback(SDL_Event&, WidgetReference);
	static void triangleSliderCallback(SDL_Event&, WidgetReference);
	// From Config, we use this to pull from a config file
/*	friend std::ostream & operator<<(std::ostream & os, const GameManager & manager)
	{
		long entityCount = manager.entityList.size();
		for(long entityIndex = 0; entityIndex < entityCount; entityIndex ++)
		{
			EntityReference entity = manager.entityList[entityIndex];
			os << *entity << std::endl;
		}
		return os;
	}*/
};

#endif
