
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

std::map<JobType, int> m = {
	{JOB_BUILD_HOUSE, 5},
	{JOB_BUILD_STONEWORKS, 5},
	{JOB_BUILD_SMELTING, 5},
	{JOB_BUILD_FARM, 5},
	{JOB_BUILD_LUMBERMILL, 5},
	{JOB_BUILD_STOREHOUSE, 5},
	{JOB_BUILD_WEAPONSMITH, 5},
	{JOB_BUILD_ARMORSMITH, 5},
	{JOB_BUILD_WATCHTOWER, 5},
	{JOB_BUILD_TOWNCENTER, 5}
};

class Job // base class
{
protected:
	JobType _type;
	int _priority;
	std::vector<TaskReference> _taskList;

public:
	Job(JobType type, int priority);
	~Job();
	void setType(JobType type);
	void setPriority(int priority);
	void virtual createTaskList() = 0;
	JobType getType();
	int getPriority();
	std::vector<TaskReference> virtual getTaskList() = 0;
	bool isCompleted();

};

class GatherJob : public Job
{
public:
	GatherJob(JobType type, int priority);
	~GatherJob();
	void createTaskList();
	std::vector<TaskReference> getTaskList();
};

class BuildJob : public Job
{
	Entity * _target;
public:
	BuildJob(JobType type, int priority, Entity * target);
	~BuildJob();
	void createTaskList();
	std::vector<TaskReference> getTaskList();
};

class MilitaryJob : public Job
{
	Entity * _target;
public:
	MilitaryJob(JobType type, int priority, Entity * target);
	~MilitaryJob();
	void createTaskList();
	std::vector<TaskReference> getTaskList();
};

#endif

typedef Job* JobReference;
