
#ifndef SDL_TRIANGLE_SLIDER_H_
#define SDL_TRIANGLE_SLIDER_H_

#include "sdl-widget.h"

class SdlTriangleSlider : public SdlWidget
{
	ImageReference background;
	ImageReference handle;

	double valueA;
	double valueB;
	double valueC;

	ImageReference createTriangleSliderBackground();
	ImageReference createTriangleSliderHandle();
	void renderTriangleSliderSurface();

	bool isInside(int xMouse, int yMouse);

public:
	SdlTriangleSlider(void (*)(SDL_Event&));
	SdlTriangleSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event));
	~SdlTriangleSlider();

	void handleEvent(SDL_Event & event);

	double getValueA() { return valueA; }
	double getValueB() { return valueB; }
	double getValueC() { return valueC; }
};

typedef SdlTriangleSlider * TriangleSliderReference;

#endif
