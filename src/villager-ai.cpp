#include "villager-ai.h"

VillagerAI::VillagerAI(int faction,int optionalOption):faction(faction),optionalOption(optionalOption),running(false),delay(1),counter(0)
{
	this->faction = faction;
	this->optionalOption = optionalOption;
}
VillagerAI::~VillagerAI()
{}

void VillagerAI::checkResource(int resource)
{
	//food, stone, wood, iron
}

void VillagerAI::balanceJobs()
{
	int total = 0;
	int average = 0;
	for(int i = 0; i < RT_COUNT; i++)
		total += getResourceAmount(ResourceType(i));
	average = total/RT_COUNT;

	for(int i = 0; i < RT_COUNT; i++)
		if(getResourceAmount(ResourceType(i)) < average)
			;//createGatherJob(ResourceType(i));

	//gather
	//create
	//	check position of building to create - another class?
	//defend
	//	check position attacked - another class?
}

void VillagerAI::getTriangleStats()
{

}

void VillagerAI::run()
{
	if(running && counter >= delay)
	{
		counter = 0;
		balanceJobs();
	}
	counter++;
}

void VillagerAI::start()
{
	running = true;
}

void VillagerAI::stop()
{
	running = false;
}
