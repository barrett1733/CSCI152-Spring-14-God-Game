
#include "job-factory-gather-wood.h"

JobReference JobFactoryGatherWood::createJob()
{
	JobGatherWood * job = new JobGatherWood();

	// do other stuff?

	return job;
}
