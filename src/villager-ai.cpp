

class VillagerAI
{
private:
	int faction;
	int optionalOption;
	int delay;
	bool running;
	void balanceJobs();
	void checkResources();
	void getTriangleStats();

public:
	VillagerAI(int,int);
	void start();
	void stop();
	void run();
};

VillagerAI::VillagerAI(int faction,int optionalOption):faction(faction),optionalOption(optionalOption),running(false),delay(1)
{
}

void VillagerAI::checkResources()
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
		checkResources();
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