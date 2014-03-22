
#ifndef JOB_H_
#define JOB_H_
#include <vector>
#include <map>
#include <stdlib.h>
#include "task.h"
#include <iostream>

enum JobType// maybe job type enum goes here
{
	JOB_NONE = 0x00,

	JOB_GATHER_FOOD = 0x01,
	JOB_GATHER_IRON,
	JOB_GATHER_WOOD,
	JOB_GATHER_STONE,
	
	JOB_BUILD_HOUSE = 0x0001,
	JOB_BUILD_STONEWORKS,
	JOB_BUILD_SMELTING,
	JOB_BUILD_FARM,
	JOB_BUILD_LUMBERMILL,
	JOB_BUILD_STOREHOUSE,
	JOB_BUILD_WEAPONSMITH,
	JOB_BUILD_ARMORSMITH,
	JOB_BUILD_WATCHTOWER,
	JOB_BUILD_TOWNCENTER,

	JOB_ATTACK = 0x000001,
	JOB_DEFEND,
	JOB_PATROL,
	JOB_TAME_1,
	JOB_PARLEY,

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
	getTaskList();
	bool isCompleted();
	void createTaskList();

};

class GatherJob : public Job
{
protected:
	void createTaskList();
public:
	GatherJob(JobType type, int priority, int taskNum, int taskQuota);
	~GatherJob();
	std::vector<TaskReference> getTaskList();
};

class BuildJob : public Job
{
protected:
	Entity * _target;
public:
	BuildJob(JobType type, int priority, int taskNum, int taskQuota, Entity * target);
	~BuildJob();
	void createTaskList();
	std::vector<TaskReference> getTaskList();
};

class MilitaryJob : public Job
{
protected:
	Entity * _target;
	void createTaskList();
public:
	MilitaryJob(JobType type, int priority, int taskNum, int taskQuota, Entity * target);
	~MilitaryJob();
	void createTaskList();
	std::vector<TaskReference> getTaskList();
};

#endif

typedef Job* JobReference;
