//
//  File: job.h
//  Author: Jimmy Ouyang
//  CSci 152
//  Spring 2014
//
//  Each job can be breaked down to a number of tasks
//  The tasks will be generated once a job is created
//  A job is completed after all the tass are completed
//
#ifndef JOB_H_
#define JOB_H_
#include <vector>
#include <map>
#include <stdlib.h>
#include <iostream>
#include "task-manager.h"

enum JobType// maybe job type enum goes here
{
	JOB_NONE = 0x00,
//Gather job type
    JOB_GATHER_RESOURCE = 0x01,
//	JOB_GATHER_FOOD = 0x01,
//	JOB_GATHER_IRON,
//	JOB_GATHER_WOOD,
//	JOB_GATHER_STONE,
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

struct ResourceCost
{
    int wood;
    int food;
    int stone;
    int iron;
};

class Job // base class
{
protected:
	JobType _type;
	int _priority;
	std::vector<TaskReference> _taskList;
	int _taskNum;
	int _taskQuota;
    static std::map<JobType, TaskType> mp;

public:
    static std::map<JobType, int> mapBuildTaskNum;
    static std::map<JobType, int> mapBuildingHealth;
	Job(JobType type, int priority);
	virtual ~Job() {};
	void setType(JobType type);
	void setPriority(int priority);
	JobType getType();
	int getPriority();
	bool isCompleted();
    void virtual createTaskList() = 0;
	std::vector<TaskReference> getTaskList();
	void cleanTaskList();
};

class GatherJob : public Job
{
protected:
    ResourceCost cost;
public:
	GatherJob(JobType type, int priority, ResourceCost);
	virtual ~GatherJob() {};
	void createTaskList();
	//std::vector<TaskReference> getTaskList();
};

class BuildJob : public Job
{
protected:
	Position _target;
public:
	BuildJob(JobType type, int priority, Position psn);
	virtual ~BuildJob() {};
	void createTaskList();
	//std::vector<TaskReference> getTaskList();
};

class MilitaryJob : public Job
{
protected:
	Position _target;
public:
	MilitaryJob(JobType type, int priority, Position psn);
	virtual ~MilitaryJob() {};
	void createTaskList();
	//std::vector<TaskReference> getTaskList();
};

#endif

typedef Job* JobReference;
