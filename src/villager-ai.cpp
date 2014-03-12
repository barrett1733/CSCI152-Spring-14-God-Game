#include "villager-ai.h"

VillagerAI::VillagerAI(int faction,int optionalOption):faction(faction),optionalOption(optionalOption),running(false),delay(1)
{
}
VillagerAI::~VillagerAI()
{}

void VillagerAI::checkResource(int resource)
{
	//food, stone, wood, iron
}

void VillagerAI::balanceJobs()
{
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
	int counter = 0;
	if(running && counter == delay)
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