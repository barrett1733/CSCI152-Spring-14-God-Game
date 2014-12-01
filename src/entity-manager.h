#pragma once
#include "entity.h"
#include "sdl/sdl-entity.h"
#include "config.h"

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

class EntityManager : public Config
{
	std::multimap<EntityGroup, EntityRecord*> recordMap;

	std::map<Faction, std::vector<EntityRecord*> > factionMap;

	std::map<EntityType, MobileEntity> entityStatsMap;

	EntityType loadingType;

	void setStats(Entity&);
	void setStats(MobileEntity&);

public:
	EntityReference createRecord(const EntityReference);
	EntityReference createRecord(const Entity&);
	void deleteRecord(); // removes entity from all applicable lists
	void update(ObstructionMapReference);

	bool setProperty(std::string property, std::string value);
	bool setProperty(std::string property, int value);

	void getEntityType();
	// needs a return of some kind, this will define what lists
	//   the entity is added to or removed from.
	EntityManager();
	~EntityManager();
};

