//
//  CSCI 152, Spring 2014, God Game
//

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Position.h"
#include "Task.h"
#include "Position.h"
#include <string>

enum EntityType {
	ET_NONE = 0x00,

	ET_TREE_1 = 0x01,
	ET_TREE_2,
	ET_SHRUB_1,
	ET_SHRUB_2,
	ET_BOULDER,

	ET_VILLAGER = 0x0100,
	ET_ELDER,
	ET_CHILD,
	ET_COW,
	ET_HORSE,
	ET_MONSTER_1,
	ET_MONSTER_2,

	ET_HOVEL = 0x010000,
	ET_HOUSE,
	ET_BARRACK,
	ET_WATCHTOWER,
	ET_GUARDTOWER,
	ET_STOCKPILE,
	ET_STOREHOUSE,
	ET_WORKSHOP_1,
	ET_WORKSHOP_2,
};

class Entity
{
public:
	std::string name;
	Position position;
	int health;
	EntityType type;
};

class MobileEntity : public Entity
{
public:
	Task task;
	int hunger;
	int faction;
};

extern Entity * EntityList;

#endif
