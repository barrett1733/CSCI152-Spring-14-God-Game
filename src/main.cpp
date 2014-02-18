#include <iostream>
#include "sdl-manager.h"

static bool running = true;

void stopRunning(SDL_Event & event)
{
	std::cout << "stop running" << std::endl;
	running = false;
}

int main(int argc, char **argv)
{
	sdl.test_setUp();

	// Main loop flag
	//bool running = true;

	sdl.subscribeToEvent(stopRunning, SDL_QUIT);
	sdl.subscribeToEvent(stopRunning, SDL_KEYDOWN, '\e');
	sdl.createButton(stopRunning, 0, "Quit", 16, 552, 128, 32);

	// While application is running
	while(running)
	{
		sdl.update();
	}

	return 0;
}
