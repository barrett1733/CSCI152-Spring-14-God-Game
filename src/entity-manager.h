#pragma once
#include "entity.h"
#include "sdl/sdl-entity.h"


struct EntityRecord
{
	Entity * entity;
	SdlEntityReference widget;

	void erase()
	{
		if (widget) widget->erase();
	}

	void update(ObstructionMapReference obstructionMap)
	{
		if (entity) entity->update(obstructionMap);
		if (widget) widget->update();
	}
};

typedef std::pair<EntityGroup, EntityRecord*> EntityRecordPair;

class EntityManager
{
	std::multimap<EntityGroup, EntityRecord*> recordMap;

	std::map<Faction, std::vector<EntityRecord*> > factionMap;


public:
	void createRecord(const EntityReference);
	void createRecord(const Entity&);
	void deleteRecord(); // removes entity from all applicable lists
	void update(ObstructionMapReference);

	void getEntityType();
	// needs a return of some kind, this will define what lists
	//   the entity is added to or removed from.
	EntityManager();
	~EntityManager();
};

