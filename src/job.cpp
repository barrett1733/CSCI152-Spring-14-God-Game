
#include "job.h"

	Job::Job(JobType type, int priority):
	_type(type), _priority(priority)
	{}

	Job::~Job(){};
	
	void Job::setType(JobType type)
	{
		this->_type = type;
	}

	void Job::setPriority(int priority)
	{
		this->_priority = priority;
	}

	JobType Job::getType()
	{
		return this->_type;
	}

	int Job::getPriority()
	{
		return this->_priority;
	}

	bool Job::isCompleted()
	{
		return _taskList.size() == 0;
	}

	//Constructor
	GatherJob::GatherJob(JobType type, int priority) : Job(type, priority){
		this.createTaskList();
	};
	//~GatherJob();

	void GatherJob::createTaskList()
	{
		//...
		//No target when a gathering atask is created, assign a target when the task is assigned to a villager
		//To create a gathering task, need to know the TaskType, Amount of Resource needed, Priority
		//Shortage of Resource: Total amount/5 * gathering cycle amount
		//Normal Gather Task: Depending on triangle value
		//						or Create a new one whenever the task list is empty
		//Task task();
		//taskList.push_back(task);
	}

	std::vector<TaskReference> GatherJob::getTaskList()
	{
		return this->_taskList;
	}

	//Constructor
	BuildJob::BuildJob(JobType type, int priority, Entity * target) : Job(type, priority), _target(target) {
		this.createTaskList();
	};
	//~BuildJob();

	//Create Build Task List
	void BuildJob::createTaskList()
	{
		for(int i=0; i<m[_type]; i++)
		{
			//Task task();
			//taskList.push_back(task);
			std::cout<<"Create a task!"<<std::endl;
		}
	}

	std::vector<TaskReference> BuildJob::getTaskList()
	{
		return this->_taskList;
	}

	//Constructor
	MilitaryJob::MilitaryJob(JobType type, int priority, Entity * target) : Job(type,priority), _target(target) {
		this.createTaskList();
	};
	//~MilitaryJob();

	//Create Military Task List
	void MilitaryJob::createTaskList()
	{
		//...
	}

	std::vector<TaskReference> MilitaryJob::getTaskList()
	{
		return this->_taskList;
	}

	int main(){
        Position p;
		Entity * entity = new Entity(ET_HOUSE, 100, p);
		JobReference job = new BuildJob(JOB_BUILD_HOUSE, 3, entity);
		delete entity;
		delete job;
	}
