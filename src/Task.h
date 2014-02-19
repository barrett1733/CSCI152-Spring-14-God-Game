//
//  CSCI 152, Spring 2014, God Game
//

#ifndef TASK_H_
#define TASK_H_

#include "Entity.h"
#include "Position.h"

enum TaskType
{
	TASK_NONE = 0x00,

	TASK_GATHER_1 = 0x01,
	TASK_GATHER_2,
	TASK_GATHER_3,
	TASK_GATHER_4,

	TASK_BUILD_HOVEL = 0x0100,
	TASK_BUILD_HOUSE,
	TASK_BUILD_BARRACK,
	TASK_BUILD_TOWER_1,
	TASK_BUILD_TOWER_2,
	TASK_BUILD_STORAGE_1,
	TASK_BUILD_STORAGE_2,
	TASK_BUILD_WORKSHOP_1,
	TASK_BUILD_WORKSHOP_2,

	TASK_ATTACK = 0x010000,
	TASK_DEFEND,
	TASK_PATROL,
	TASK_TAME_1,
	TASK_TAME_2,
	TASK_PARLEY,
};

class Task
{
public:
	TaskType type;
	Entity * target;
	Position * source;
	Position * destination;
};

#endif
