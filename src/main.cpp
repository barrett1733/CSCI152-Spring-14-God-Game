
#include <iostream>
#include <sstream>
#include "game-manager.h"
#include "sdl-triangle-slider.h"

static TriangleSliderReference triangleSlider;
static TextDisplayReference textDisplay = 0;
static TextDisplayReference textDisplayA = 0;
static TextDisplayReference textDisplayB = 0;
static TextDisplayReference textDisplayC = 0;

inline std::string toString(double x)
{
  std::ostringstream o;
  o << x;
  return o.str();
}

void sliderCallback(SDL_Event & event)
{
	std::string text;
	double a = triangleSlider->getValueA();
	double b = triangleSlider->getValueB();
	double c = triangleSlider->getValueC();
	double t = a + b + c;

	text = "";
	text += toString(a);
	textDisplayA->setText(text);

	text = "";
	text += toString(b);
	textDisplayB->setText(text);

	text = "";
	text += toString(c);
	textDisplayC->setText(text);

	text = "";
	text += toString(t);
	textDisplay->setText(text);

	std::cout << "Slider set: "
		<< a << " + "
		<< b << " + "
		<< c << " = "
		<< t << std::endl;
}

int main(int argc, char **argv)
{




	GameManager game;

	return 0;
}
