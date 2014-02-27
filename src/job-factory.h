
#ifndef JOB_FACTORY_H_
#define JOB_FACTORY_H_

#include "job.h"

typedef int JobType; // we change easily change this to an enum, or just use multi character constants

class JobFactory // interface class
{
protected:
	JobType jobType;

	void createTaskList(JobReference job); // called by 'createJob()'

public:
	bool canCreate(JobType & type)
	{
		return type == jobType;
	}

	virtual JobReference createJob() = 0; // implemented by inheriting class
};

#endif
