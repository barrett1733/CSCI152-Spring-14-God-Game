#include "miracle-entity.h"

miracle-entity(EntityType, int health, Position, Faction):Entity(EntityType, int health, Position, Faction){}

miracle-entity(const Entity&):Entity(const Entity&){}

void update(){};