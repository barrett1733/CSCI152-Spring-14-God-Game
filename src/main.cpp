
#include <iostream>
#include <sstream>
#include "sdl-manager.h"

static bool running = true;
static SliderReference slider = 0;
static TextDisplayReference textDisplay = 0;

inline std::string toString(double x)
{
  std::ostringstream o;
  o << x;
  return o.str();
}

void sliderCallback(SDL_Event & event)
{
	std::string text;
	text += toString(100 * slider->getValue());
	text += "%";
	std::cout << "Slider set: " << slider->getValue() << std::endl;
	textDisplay->setText(text);
}

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
	slider = sdl.createSlider(sliderCallback, 0, 16, 200);
	textDisplay = sdl.createTextDisplay("", 16+256+16, 200);

	// While application is running
	while(running)
	{
		sdl.update();
	}

	return 0;
}
