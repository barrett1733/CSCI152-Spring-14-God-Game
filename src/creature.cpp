#include "creature.h"


Creature::Creature()
{ }
Creature::Creature(Faction faction) : faction(faction)
{ }

void Creature::decideRun()
{

}

void Creature::decideWalk()
{

}

void Creature::run()
{
	decideRun();
	decideWalk();
}