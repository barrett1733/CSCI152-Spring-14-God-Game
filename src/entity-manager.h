#pragma once
#include "entity.h"
#include "sdl\sdl-entity.h"

enum EntityRecordList
{
	EL_ALL,
	EL_VILLAGE,
	EL_WIDGET,
	EL_PEACEFUL,
	EL_ENEMY,
	EL_BUILDING,

	EL_COUNT
};

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
	std::vector<std::vector<EntityRecord*>> recordList;
	std::vector<EntityReference> entityList;
	std::vector<WidgetReference> widgetList;

	std::map<Faction, std::vector<EntityRecord*> > factionMap;


public:
	void createRecord(const EntityReference);
	void createRecord(const Entity&);
	void addWidget(WidgetReference);
	void addEntity();
	void deleteEntity(); // removes entity from all applicable lists
	void update(ObstructionMapReference);

	void getEntityType();
	// needs a return of some kind, this will define what lists
	//   the entity is added to or removed from.
	EntityManager();
	~EntityManager();
};

