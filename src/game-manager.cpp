//
//  File: entity-manager.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Entity Manager Implementation
//

#include <iostream>

#include "game-manager.h"

GameManager * GameManager::self = 0;
std::map<std::string, void (*)(SDL_Event&, WidgetReference)> GameManager::callbackMap;
bool GameManager::callbackMapInitialized = false;
VillageManager GameManager::villageManager;
EntityManager GameManager::entityManager;
WidgetContainerReference GameManager::buttonContainer = 0;

GameManager::GameManager() :
	worldSize(0),
	visible(false)
{
	if(self)
	{
		std::cerr << "\033[31m GameManager already exists!\033[m" << std::endl;
		return;
	}
	self = this;

}

void GameManager::setup()
{
	WorldGeneration world(time(0));
	worldSize = world.getWorldSize();

	initializeCallbackMap();
	buttonContainer = new SdlWidgetContainer(callbackMap, "res/sidebar.cfg");

	mapView = new SdlMapView();
	mapView->hide();

	SdlEntity::mapView = mapView;
	SdlEntity::worldSize = worldSize;

	//  Village Manager
	villageManager.show();
	villageManager.addVillage(F_PLAYER_1);
	villageManager.addVillage(F_PLAYER_2);
	hide();

	obstructionMap = new ObstructionMap(worldSize);


	EntityReference entity = world.getNextEntity();
	while (entity && entity->getType() != ET_NONE)
	{
		entityManager.createRecord(entity);

		// Get next entity for next loop iteration.
		delete entity;
		entity = world.getNextEntity();
	}
}


void GameManager::update()
{
	if(!visible) show();

	villageManager.update(obstructionMap);

	entityManager.update(obstructionMap);

	// ...
}

void GameManager::show()
{
	if(visible) return;
	std::cout << "GameManager::show()" << std::endl;
	visible = true;
	villageManager.show();
	mapView->show();
	buttonContainer->show();
	// unsigned long count = widgetList.size();
	// for(int index = 0; index < count; index ++)
	// 	widgetList[index]->show();
}

void GameManager::hide()
{
	villageManager.hide();
	if(!visible) return;
	std::cout << "GameManager::hide()" << std::endl;
	visible = false;
	mapView->hide();
	buttonContainer->hide();
}


//

void GameManager::initializeCallbackMap()
{
	if(callbackMapInitialized) return;
	callbackMapInitialized = true;

	callbackMap["build()"] = build;
	callbackMap["miracle()"] = miracle;

	callbackMap["triangleSliderCallback()"] = triangleSliderCallback;
	callbackMap["sliderCallback()"] = sliderCallback;
}

//

void GameManager::build(SDL_Event & event, WidgetReference widget)
{
	std::cout << "GameManager::build(" << widget->id << ")" << std::endl;
	if(self)
	{
		Faction faction = F_PLAYER_1;
		EntityType type = (EntityType) widget->id;
		VillageReference village = villageManager.getVillage(faction);
		EntityReference townCenter = village->getTownCenter();

		if(!townCenter)
			std::cerr << "No town center." << std::endl;
		else
		{
			Position origin = townCenter->getPosition();
			Position position = self->obstructionMap->findOpenPosition(origin);

			EntityReference entity = new Entity(type, 1, position, faction);
			entityManager.createRecord(entity);

			//self->obstructionMap->set(position, OT_CONSIDERED);

			//std::cout << (*(self->obstructionMap)) << std::endl;
		}

		//self->villageManager.buildHouse();
	}
	else
		std::cerr << "GameManager not initialized." << std::endl;
}

void GameManager::miracle(SDL_Event & event, WidgetReference widget)
{
	std::cout << "GameManager::miracle(" << widget->id << ")" << std::endl;
	if(self)
	{
		//  NOTE: widget->id is the MiracleType (needs to be cast).
		Faction faction = F_PLAYER_1;
		EntityType type = (EntityType) widget->id;
		VillageReference village = villageManager.getVillage(faction);
		EntityReference townCenter = village->getTownCenter();

		if(!townCenter)
			std::cout << "No town center." << std::endl;
		else if(!type)
			std::cout << "No type." << std::endl;
		else if(0)
		{
			Position origin = townCenter->getPosition();
			Position position = origin;

			EntityReference entity = new MiracleEntity(type, 1, position, faction);
			//self->createRecord(entity);
		}
		else
			std::cout << "Type: " << type << ", but not implemented." << std::endl;

	}
	else
		std::cerr << "GameManager not initialized." << std::endl;
}

void GameManager::sliderCallback(SDL_Event & event, WidgetReference widget)
{

}

void GameManager::triangleSliderCallback(SDL_Event & event, WidgetReference widget)
{

}

