//
//  File: sdl-triangle-slider.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Triangle Slider Widget Defintion
// Extends the generic Widget Class.
// Provides an interactive triangular slider interface.
// Values for each point of the trangle range from 0 to 1.
// Values are calculated as the orthongonal distance from the opposite edge.
// The methods getValueA(), getValueB(), and getValueC() provide the
// values for the top, bottom right, and bottom left values.
//

#ifndef SDL_TRIANGLE_SLIDER_H_
#define SDL_TRIANGLE_SLIDER_H_

#include "sdl-widget.h"

class SdlTriangleSlider : public SdlWidget
{
	static const int padding = 4;

	ImageReference background;
	ImageReference handle;

	double valueA;
	double valueB;
	double valueC;

	void (*liveCallback)(SDL_Event&,WidgetReference);

	ImageReference createTriangleSliderBackground();
	ImageReference createTriangleSliderHandle();
	void renderTriangleSliderSurface();

	bool isInside(int xMouse, int yMouse);

public:
	SdlTriangleSlider(SDL_Rect & rect, void (*)(SDL_Event&, WidgetReference));
	SdlTriangleSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference));
	SdlTriangleSlider(SDL_Rect & rect, void (*)(SDL_Event&, WidgetReference), void (*)(SDL_Event&, WidgetReference));
	SdlTriangleSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference), void (*)(SDL_Event&, WidgetReference));
	~SdlTriangleSlider();

	void handleEvent(SDL_Event & event);

	double getValueA() { return valueA; }
	double getValueB() { return valueB; }
	double getValueC() { return valueC; }
};

typedef SdlTriangleSlider * TriangleSliderReference;

#endif
