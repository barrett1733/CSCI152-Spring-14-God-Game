//
//  File: entity.cpp
//  Author: Chad Hatcher, Steven Barrett
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Entity Class Implementation
//  Mobile Entity Class Implementation
//

#include "entity.h"
#include "job/task.h"
#include "movement/pathfinding.h"

Entity::Entity(EntityType type, int health, Position position, Faction faction) :
	type(type),
	faction(faction),
	maxHealth(health),
	currentHealth(health),
	position(position)
{
	if(type < ET_RESOURCE)      group = EG_NONE;
	else if(type < ET_VILLAGER) group = EG_RESOURCE;
	else if(type < ET_DOMESTIC) group = EG_VILLAGER;
	else if(type < ET_PASSIVE)  group = EG_DOMESTIC;
	else if(type < ET_HOSTILE)  group = EG_PASSIVE;
	else if(type < ET_BUILDING) group = EG_HOSTILE;
	else if(type < ET_MIRACLE)  group = EG_BUILDING;
	else                        group = EG_MIRACLE;
}

Entity::Entity(EntityType type, Position position, Faction faction) :
	type(type),
	faction(faction),
	maxHealth(0),
	currentHealth(0),
	position(position)
{
	if(type < ET_RESOURCE)      group = EG_NONE;
	else if(type < ET_VILLAGER) group = EG_RESOURCE;
	else if(type < ET_DOMESTIC) group = EG_VILLAGER;
	else if(type < ET_PASSIVE)  group = EG_DOMESTIC;
	else if(type < ET_HOSTILE)  group = EG_PASSIVE;
	else if(type < ET_BUILDING) group = EG_HOSTILE;
	else if(type < ET_MIRACLE)  group = EG_BUILDING;
	else                        group = EG_MIRACLE;

}

Entity::Entity(Position position) :
	type(ET_NONE),
	group(EG_NONE),
	faction(F_NONE),
	maxHealth(0),
	currentHealth(0),
	position(position)
{ }

Entity::Entity(const Entity & entity) :
	group(entity.group),
	type(entity.type),
	faction(entity.faction),
	maxHealth(entity.maxHealth),
	currentHealth(entity.currentHealth),
	position(entity.position)
{ }

Entity::~Entity()
{
}

Entity& Entity::operator= (const Entity& entity)
{
	name = entity.name;
	group = entity.group;
	type = entity.type;
	faction = entity.faction;
	position = entity.position;
	currentHealth = entity.currentHealth;
	maxHealth = entity.maxHealth;

	return *this;
}

std::string Entity::getName() const
{
	return name;
}

EntityGroup Entity::getGroup() const
{
	return group;
}

EntityType Entity::getEntityType() const
{
	return type;
}

EntityType Entity::getType() const
{
	return type;
}

Position Entity::getPosition() const
{
	return position;
}

Faction Entity::getFaction() const
{
	return faction;
}

int Entity::getMaxHealth() 
{
	return maxHealth;
}
int Entity::getCurrentHealth() 
{
	return currentHealth;
}
int Entity::getHealth() const
{
	return currentHealth;
}


void Entity::setName(std::string name_)
{
	name = name_;
}
void Entity::setGroup(EntityGroup group_)
{
	group = group_;
}
void Entity::setEntityType(EntityType type_)
{
	type = type_;
}
void Entity::setFaction(Faction faction_)
{
	faction = faction_;
}
void Entity::setMaxHealth(int maxHealth_)
{
	maxHealth = maxHealth_;
}
void Entity::setCurrentHealth(int currentHealth_)
{
	currentHealth = currentHealth_;
}
void Entity::setHealth(int health)
{
	currentHealth = health;
	if(maxHealth == 0)
		maxHealth = health;
	if(currentHealth > maxHealth)
		currentHealth = maxHealth;
}
void Entity::setPosition(Position position_)
{
	position = position;
}
