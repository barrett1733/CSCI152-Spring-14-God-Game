
#ifndef JOB_H_
#define JOB_H_
#include <vector>
#include <map>
#include <stdlib.h>
#include <iostream>
#include "taskManager.h"

enum JobType// maybe job type enum goes here
{
	JOB_NONE = 0x00,
//Gather job type
	JOB_GATHER_FOOD = 0x01,
	JOB_GATHER_IRON,
	JOB_GATHER_WOOD,
	JOB_GATHER_STONE,
//Build job type
	JOB_BUILD_HOUSE = 0x100,
	JOB_BUILD_SMELTING,
	JOB_BUILD_FARM,
	JOB_BUILD_LUMBERMILL,
	JOB_BUILD_STONEWORKS,
	JOB_BUILD_WEAPONSMITH,
	JOB_BUILD_ARMORSMITH,
	JOB_BUILD_WATCHTOWER,
	JOB_BUILD_TOWNCENTER,
	JOB_BUILD_TEMPLE,
//Military job type
	JOB_ATTACK = 0x10000,
	JOB_DEFEND,
	JOB_PATROL,
	JOB_TAME_1,
	JOB_PARLEY
};

static std::map<JobType, TaskType> mp = {
	{JOB_GATHER_FOOD, TASK_GATHER_FOOD},
	{JOB_GATHER_IRON, TASK_GATHER_IRON},
	{JOB_GATHER_WOOD, TASK_GATHER_WOOD},
	{JOB_GATHER_STONE, TASK_GATHER_STONE},
	
	{JOB_BUILD_HOUSE, TASK_BUILD_HOUSE},
	{JOB_BUILD_STONEWORKS, TASK_BUILD_STONEWORKS},
	{JOB_BUILD_SMELTING, TASK_BUILD_SMELTING},
	{JOB_BUILD_FARM, TASK_BUILD_FARM},
	{JOB_BUILD_LUMBERMILL, TASK_BUILD_LUMBERMILL},
	{JOB_BUILD_WEAPONSMITH, TASK_BUILD_WEAPONSMITH},
	{JOB_BUILD_ARMORSMITH, TASK_BUILD_ARMORSMITH},
	{JOB_BUILD_WATCHTOWER, TASK_BUILD_WATCHTOWER},
	{JOB_BUILD_TOWNCENTER, TASK_BUILD_TOWNCENTER},
	{JOB_BUILD_TEMPLE, TASK_BUILD_TEMPLE}
};

class Job // base class
{
protected:
	JobType _type;
	int _priority;
	std::vector<TaskReference> _taskList;
	int _taskNum;
	int _taskQuota;

public:
	Job(JobType type, int priority, int taskNum, int taskQuota);
	~Job();
	void setType(JobType type);
	void setPriority(int priority);
	JobType getType();
	int getPriority();
	bool isCompleted();
	virtual void createTaskList() = 0;
	std::vector<TaskReference> getTaskList();
};

class GatherJob : public Job
{
public:
	GatherJob(JobType type, int priority, int taskNum, int taskQuota);
	~GatherJob();
    void createTaskList();
	//std::vector<TaskReference> getTaskList();
};

class BuildJob : public Job
{
protected:
	Entity * _target;
public:
	BuildJob(JobType type, int priority, int taskNum, int taskQuota, Entity * target);
	~BuildJob();
	void createTaskList();
	//std::vector<TaskReference> getTaskList();
};

class MilitaryJob : public Job
{
protected:
	Entity * _target;
public:
	MilitaryJob(JobType type, int priority, int taskNum, int taskQuota, Entity * target);
	~MilitaryJob();
	void createTaskList();
	//std::vector<TaskReference> getTaskList();
};

#endif

typedef Job* JobReference;
