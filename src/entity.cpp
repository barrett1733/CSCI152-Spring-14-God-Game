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

Entity::Entity() :
	group(EG_NONE),
	type(ET_NONE),
	faction(F_NONE),
	maxHealth(0),
	currentHealth(0),
	position()
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
	return this->name;
}

EntityGroup Entity::getGroup() const
{
	return this->group;
}

EntityType Entity::getEntityType() const
{
	return this->type;
}

EntityType Entity::getType() const
{
	return this->type;
}

Position Entity::getPosition() const
{
	return this->position;
}

Faction Entity::getFaction() const
{
	return this->faction;
}

int Entity::getMaxHealth() {
	return this->maxHealth;
}
int Entity::getCurrentHealth() {
	return this->currentHealth;
}
int Entity::getHealth() const
{
	return currentHealth;
}


void Entity::setName(std::string name)
{
	this->name = name;
}
void Entity::setGroup(EntityGroup group)
{
	this->group = group;
}
void Entity::setEntityType(EntityType type)
{
	this->type = type;
}
void Entity::setFaction(Faction faction)
{
	this->faction = faction;
}
void Entity::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}
void Entity::setCurrentHealth(int currentHealth)
{
	this->currentHealth = currentHealth;
}
void Entity::setHealth(int health)
{
	currentHealth = health;
	if(maxHealth == 0)
		maxHealth = health;
	if(currentHealth > maxHealth)
		currentHealth = maxHealth;
}
void Entity::setPosition(Position position)
{
	this->position = position;
}

////////
//  MOBILE ENTITY
////////

MobileEntity::MobileEntity() :
	Entity(),
	task(0),
	target(0)
{}

MobileEntity::MobileEntity(const Entity & entity) :
	Entity(entity),
	task(0),
	target(0)
{}

int MobileEntity::getHunger() {
	return this->hunger;
}
int MobileEntity::getStrength() {
	return this->strength;
}
int MobileEntity::getDefense() {
	return this->defense;
}
double MobileEntity::getSightRange() {
	return this->sightRange;
}
Entity* MobileEntity::getTarget() {
	return this->target;
}

void MobileEntity::setHunger(int hunger) {
	this->hunger = hunger;
}
void MobileEntity::setStrength(int strength) {
	this->strength = strength;
}
void MobileEntity::setDefense(int defense) {
	this->defense = defense;
}
void MobileEntity::setSightRange(double range) {
	this->sightRange = range;
}
void MobileEntity::setTarget(Entity* target) {
	this->target = target;
}

bool MobileEntity::hasTask()
{
	return task ? true : false;
}

void MobileEntity::setTask(TaskReference task)
{
	if(task)
	{
		this->task = task;
		this->target = task->getTarget();
	}
	else
	{
		this->task = 0;
		this->target = 0;
		// worship or wander?
	}
}

void MobileEntity::update(ObstructionMapReference obstructionMap)
{/*
	Pathfinding test;
	PositionList* toMove;
	toMove = test.findPath(Position(0, 0), this->getPosition(), obstructionMap);
	if (!toMove->empty())
		this->setPosition(toMove->at(0));
	
	if(target)
	{
		Direction direction = D_NONE;
		int targetX = target->getPosition().getX();
		int targetY = target->getPosition().getY();
		int sourceX = position.getX();
		int sourceY = position.getY();

		if(targetX < sourceX)
			direction |= D_LEFT;
		else if(targetX > sourceX)
			direction |= D_RIGHT;

		if(targetY < sourceY)
			direction |= D_UP;
		else if(targetY > sourceY)
			direction |= D_DOWN;

		if(direction == D_NONE && task)
			;//task->work();

		// TODO: if(!canMove(direction)) adjust(direction);
		//

		position.move(direction);
	}
	else
	{
		int r = rand();
		switch(r % 4)
		{
			case 0:
				position.move(D_UP);
				break;

			case 1:
				position.move(D_RIGHT);
				break;

			case 2:
				position.move(D_DOWN);
				break;

			case 3:
				position.move(D_LEFT);
				break;
		}
	}*/
}
