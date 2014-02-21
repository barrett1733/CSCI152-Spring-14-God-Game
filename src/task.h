//
//  CSCI 152, Spring 2014, God Game
//

#ifndef TASK_H_
#define TASK_H_

#include "entity.h"
#include "position.h"

enum TaskType
{
	TASK_NONE,

	TASK_GATHER_FOOD,
	TASK_GATHER_MINE,
	TASK_GATHER_WOOD,
	TASK_GATHER_STONE,

	TASK_BUILD_HOVEL,
	TASK_BUILD_HOUSE,
	TASK_BUILD_BARRACK,
	TASK_BUILD_TOWER,
	TASK_BUILD_STORAGE,
	TASK_BUILD_WORKSHOP,

	TASK_ATTACK,
	TASK_DEFEND,
	TASK_PATROL,
	TASK_TAME_1,
	TASK_PARLEY,
};

class Task
{
public:
	TaskType type;
	Entity * target;
	//Position * source;
	Position * destination;
};

#endif
