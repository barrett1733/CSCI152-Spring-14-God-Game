
#include "entity.h"

//Entity * EntityList[MAX_ENTITY_COUNT];

Entity::Entity(EntityType entityType, int health, Position position, FactionType faction) :
	type(entityType),
	position(position),
	maxHealth(health),
	currentHealth(health),
	faction(faction)
{ }

Entity::Entity(EntityType entityType, int health, int xPos, int yPos, FactionType faction) :
	type(entityType),
	maxHealth(health),
	currentHealth(health),
	faction(faction)
{
	position.x = xPos;
	position.y = yPos;
}

EntityType Entity::getEntityType() {
	return this->type;
}
std::string Entity::getName() {
	return this->name;
}
int Entity::getMaxHealth() {
	return this->maxHealth;
}
int Entity::getCurrentHealth() {
	return this->currentHealth;
}
Position Entity::getPosition() {
	return this->position;
}
FactionType Entity::getFactionType() {
	return this->faction;
}

void Entity::setEntityType(EntityType type) {
	this->type = type;
}
void Entity::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}
void Entity::setCurrentHealth(int currentHealth) {
	this->currentHealth = currentHealth;
}
void Entity::setName(std::string name) {
	this->name = name;
}
void Entity::setPosition(Position position) {
	this->position = position;
}
void Entity::setFactionType(FactionType faction) {
	this->faction = faction;
}

MobileEntity::MobileEntity(EntityType entityType, int health, Position position, FactionType faction, int hunger, int strength, int defense):
	Entity(entityType, health, position, faction),
	hunger(hunger), 
	strength(strength), 
	defense(defense)
{ }
MobileEntity::MobileEntity(EntityType entityType, int health, int xPos, int yPos, FactionType faction, int hunger, int strength, int defense):
	Entity(entityType, health, xPos, yPos, faction),
	hunger(hunger), 
	strength(strength), 
	defense(defense)
{ }

int MobileEntity::getHunger() {
	return this->hunger;
}
int MobileEntity::getStrength() {
	return this->strength;
}
int MobileEntity::getDefense() {
	return this->defense;
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
