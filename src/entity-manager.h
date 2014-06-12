#pragma once
#include "entity.h"
#include "sdl\sdl-entity.h"

struct EntityRecord
{
	Entity * entity;
	SdlEntityReference widget;

	void update(std::vector<EntityReference>& entityList, ObstructionMapReference obstructionMap)
	{
		if (entity) entity->update(entityList, obstructionMap);
		if (widget) widget->update();
	}
};
class EntityManager
{
	std::vector<EntityRecord*> recordList;
	std::vector<EntityReference> entityList;
	std::vector<WidgetReference> widgetList;

	std::map<Faction, std::vector<EntityRecord*> > factionMap;
	// these lists are sub-catagories of the entitylist, should still be the same reference //
	std::vector<EntityRecord*> villagerList;
	std::vector<EntityRecord*> peacefulMobList;
	std::vector<EntityRecord*> enemyList;
	std::vector<EntityRecord*> buildingList;
	void update();


public:
	EntityRecord * createRecord(const EntityReference);
	EntityRecord * createRecord(const Entity&);
	void addWidget(WidgetReference);
	void addEntity();
	void deleteEntity(); // removes entity from all applicable lists

	void getEntityType();
	// needs a return of some kind, this will define what lists
	//   the entity is added to or removed from.
	EntityManager();
	~EntityManager();
};

