//
//  File: entity.h
//  Author: Chad Hatcher, Steven Barrett
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Entity Class Definition
// Maintains a collection of Entity properties.
//
//  Mobile Entity Class Defintion
// Extends Entity class.
// Maintains a collection of MobileEntity properties.
// Invokes pathfinding when it has a task.
//

#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <vector>
#include "movement/position.h"
#include "movement/obstruction-map.h"
#include "movement/PathMemory.h"

class Task; // forward declaration of Task class.
typedef Task * TaskReference;

enum Faction {
	F_NONE,
	F_RESOURCE,
	F_ANIMAL_DOMESTIC, // Should not exist. Domistics belong to a village faction. -CH
	F_ANIMAL_PASSIVE,
	F_ANIMAL_HOSTILE,
	F_PLAYER_1,
	F_PLAYER_2,
	F_PLAYER_3,
	F_PLAYER_4,
	F_PLAYER_5,
	F_PLAYER_6,
	F_PLAYER_7,
	F_PLAYER_8,

	F_COUNT
};

enum EntityGroup {
	EG_NONE,
	EG_RESOURCE,
	EG_BUILDING,
	EG_MIRACLE,

	EG_MOBILE, // if entity.group < EG_MOBILE, then entity isn't mobile

	EG_VILLAGER,
	EG_DOMESTIC,
	EG_PASSIVE,
	EG_HOSTILE,
};

enum EntityType {
	ET_NONE = 0x00,

	// RESOURCES
	ET_RESOURCE = 0x00000001, // NOTE: Marker. Do not change.
	ET_TREE,
	ET_TREE_2,
	ET_SHRUB_1,
	ET_SHRUB_2,
	ET_BOULDER,
	ET_STONE,
	ET_COAL,
	ET_IRON,
	ET_GOLD,
	ET_COPPER,

	// VILLAGERS
	ET_VILLAGER = 0x00000100,

	ET_ELDER_VILLAGER,
	ET_CHILD_VILLAGER,

	// DOMESTIC ANIMALS
	ET_DOMESTIC = 0x00000200, // NOTE: Marker. Do not change.
	ET_COW,

	ET_SHEEP,
	ET_HORSE,
	ET_CHICKEN,
	ET_PIG,
	ET_FISH,

	// PASSIVE
	ET_PASSIVE = 0x00000300, // NOTE: Marker. Do not change.
	ET_DEER,

	// HOSTILE
	ET_HOSTILE = 0x00000400, // NOTE: Marker. Do not change.
	ET_WOLF,
	ET_OGRE,

	ET_BOAR,
	ET_FOX,
	ET_VAMPIRE,
	ET_WEREWOLF,
	ET_HARPY,
	ET_SNOW_TROLL,
	ET_SIREN,
	ET_CTHULHU,
	ET_UNICORN,
	ET_CYCLOPS,

	// BUILDINGS
	ET_BUILDING = 0x00010000, // NOTE: Marker. Do not change.

	// In-Game buildings
	ET_TOWN_CENTER,
	ET_TEMPLE,
	ET_HOUSE = 0x00020001, //  NOTE: Do not change.
	ET_MILL, //  NOTE: Do not change.
	ET_MASONRY, //  NOTE: Do not change.
	ET_FOUNDARY, //  NOTE: Do not change.
	ET_SMITH, //  NOTE: Do not change.
	ET_ARMORY, //  NOTE: Do not change.

	ET_FOUNDATION,
	ET_STOREHOUSE,
	ET_STONEWORKS,
	ET_LUMBERMILL,
	ET_SMELTER,
	ET_WEAPONSMITH,
	ET_ARMORSMITH,
	ET_FARM,
	ET_HOVEL,
	ET_MANSION,
	ET_QUARRY,
	ET_WATCHTOWER,
	ET_MINES,

	//Miracles
	ET_MIRACLE = 0x00100000, // NOTE: Marker. Do not change.
	ET_MIRACLE_HEAL = 0x00100001, //  NOTE: Do note change.
	ET_MIRACLE_SUMMONCOW, //  NOTE: Do note change.
	ET_MIRACLE_STATBOOST, //  NOTE: Do note change.
	ET_MIRACLE_LIGTNING, //  NOTE: Do note change.
	ET_MIRACLE_EARTHQUAKE, //  NOTE: Do note change.
	ET_MIRACLE_METEOR
};

class Entity
{
private:
	std::string name;
	EntityGroup group;
	EntityType type;
	Faction faction;
	int maxHealth;
	int currentHealth;

protected:
	Position position;

public:
	Entity(EntityType, int health, Position, Faction);
	Entity(EntityType, Position, Faction);
	Entity(Position);
	Entity(const Entity&);
	Entity();

	virtual ~Entity();

	Entity& operator= (const Entity&);

	std::string getName() const;
	EntityGroup getGroup() const;
	EntityType getEntityType() const;
	EntityType getType() const;
	Faction getFaction() const;
	Position getPosition() const;
	int getMaxHealth();
	int getCurrentHealth();
	int getHealth() const;

	void setName(std::string);
	void setGroup(EntityGroup);
	void setEntityType(EntityType);
	void setFaction(Faction);
	void setMaxHealth(int);
	void setCurrentHealth(int);
	void setPosition(Position);
	void setHealth(int health);

	virtual void update(ObstructionMapReference obstructionMap) {}
	virtual void update(std::vector<Entity*>& entityList, ObstructionMapReference obstructionMap) {}

	bool operator==(EntityType type) { return this->type == type; }

	friend std::ostream& operator<< (std::ostream & os, const Entity & entity)
	{
		if(entity.name.length()) os << entity.name << " ";
		os << entity.type << " ";
		os << entity.faction << " ";
		os << entity.position << " ";
		os << entity.currentHealth << "/" << entity.maxHealth;
		return os;
	}
};

class MobileEntity : public Entity, public PathMemory
{
private:
	int hunger;
	int strength;
	int defense;
	double sightRange;

	TaskReference task;
	Entity * target;
public:
	MobileEntity();
	MobileEntity(const Entity&);
	int getHunger();
	int getStrength();
	int getDefense();
	double getSightRange();
	Entity* getTarget();
	void setHunger(int);
	void setStrength(int);
	void setDefense(int);
	void setSightRange(double);
	void setTarget(Entity*);

	void update(ObstructionMapReference obstructionMap);

	bool hasTask();
	void setTask(TaskReference);
};

#endif

typedef Entity * EntityReference;
typedef MobileEntity * MobileEntityReference;
