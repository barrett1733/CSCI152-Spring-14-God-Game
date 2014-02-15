#include <iostream>
#include "sdl-manager.h"

int main(int argc, char **argv)
{
	sdl.test_setUp();

	// Main loop flag
	bool running = true;

	// While application is running
	while( running )
	{
		running = sdl.update();
	}

	return 0;
}
