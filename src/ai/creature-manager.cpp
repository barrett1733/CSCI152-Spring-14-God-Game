#include "creature-manager.h"

CreatureManager::CreatureManager()
{
	creatureList.reserve(50);
	villagerList.reserve(50);
}

void CreatureManager::import(Entity* entity)
{
	// issue with import
	// importing everything for some reason
	EntityGroup group = entity->getGroup();
	if (group == EG_DOMESTIC || group == EG_HOSTILE || group == EG_PASSIVE)
		creatureList.push_back((MobileEntityReference)entity);
	if (group == EG_VILLAGER)
		villagerList.push_back((MobileEntityReference)entity);
}

void CreatureManager::decideAction()
{
	// test
	//for (int i = 0; i < villagerList.size(); i++)
	//	villagerList[i]->setTarget(creatureList[0]);

	// cows always wander
	// deer wander until see another mobileEntity that is not deer
	// wolves wander until see another target that is not wolf or orge
	// orges do the same as wolves
	/*
	for (int curCreature = 0; curCreature < creatureList.size(); curCreature++)
	{
		EntityGroup creatureGroup = creatureList[curCreature]->getGroup();
		if (creatureGroup == EG_DOMESTIC)
		{
			wander(creatureList[curCreature]);
		}
		if (creatureGroup == EG_PASSIVE)
		{
			Direction dir = flee(creatureList[curCreature]);
			Position pos = creatureList[curCreature]->getPosition();
			if (dir == D_NONE)
				wander(creatureList[curCreature]);
			else
			{
				obstructionMap->set(pos, OT_EMPTY);
				pos.move(dir);
				obstructionMap->set(pos, OT_OBSTRUCTED);
				creatureList[curCreature]->setPosition(pos);
			}
		}
		if (creatureGroup == EG_HOSTILE)
		{
			wander(creatureList[curCreature]);
		}
	}*/
}

void CreatureManager::wander(MobileEntity* mobileEntity)
{
	Position pos = mobileEntity->getPosition();
	obstructionMap->set(pos, OT_EMPTY);
	std::vector<Position> openPositions;
	for (int dir = D_NORTH; dir < D_COUNT; dir++)
	{
		Position neighbor = pos.getNeighbor(dir);
		if (obstructionMap->isOpen(neighbor))
			openPositions.push_back(neighbor);
	}
	pos = openPositions[rand() % openPositions.size()];
	obstructionMap->set(pos, OT_OBSTRUCTED);
	mobileEntity->setPosition(pos);
}

void CreatureManager::attack(MobileEntity* mobileEntity)
{
	// Detect entities in range
	// Wolves and orges attack everything not hostile
	// -SB
}

Direction CreatureManager::flee(MobileEntity* mobileEntity)
{
	Direction bestDir = D_NONE;
	int bestScoreIndex = 0;
	int scores[D_COUNT - D_NORTH];
	for (int i = 0; i < D_COUNT - D_NORTH; i++)
		scores[i] = 0;
	for (int i = 0; i < creatureList.size(); i++)
	{
		if (inRange(mobileEntity->getPosition(), creatureList[i]->getPosition(), mobileEntity->getSightRange()) &&
				creatureList[i]->getGroup() == EG_HOSTILE)
			for (int dir = D_NORTH; dir < D_COUNT; dir++)
			{
				evaluateFleeDirection(mobileEntity, creatureList[i], dir);

			}
	}

	for (int i = 0; i < villagerList.size(); i++)
	{
		if (inRange(mobileEntity->getPosition(), villagerList[i]->getPosition(), mobileEntity->getSightRange()) &&
				villagerList[i]->getGroup() == EG_HOSTILE)
			for (int dir = D_NORTH; dir < D_COUNT; dir++)
			{
				evaluateFleeDirection(mobileEntity, villagerList[i], dir);

			}
	}
	for (int i = 0; i < D_COUNT - D_NORTH; i++)
	{
		if (scores[bestScoreIndex] < scores[i])
		{
			bestScoreIndex = i;
		}
	}
	return bestScoreIndex;
}

void CreatureManager::update(ObstructionMap* obsMap)
{
	obstructionMap = obsMap;
	decideAction();
}

bool CreatureManager::inRange(Position origin, Position enemy, double sightrange)
{
	if (origin.distance(enemy) <= sightrange)
	{
		return true;
	}
	return false;
}

int CreatureManager::evaluateFleeDirection(MobileEntity* creature, MobileEntity* enemy, Direction dir)
{
	Position creaturePos = creature->getPosition();
	Position enemyPos = enemy->getPosition();
	int score = 0;

	Position neighbor = creaturePos.getNeighbor(dir);
	if (obstructionMap->isOpen(neighbor))
	{
		score += neighbor.distance(enemyPos);

	}
	return score;
}
