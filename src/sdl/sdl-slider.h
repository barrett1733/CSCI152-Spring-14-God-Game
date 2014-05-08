//
//  File: sdl-slider.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Slider Widget Definition
// Extends the generic Widget Class.
// Renders an interactive slider control.
// Values range from 0 on the left to 100 on the right.
// Two callbacks are available:
//  A standard callback for when the slider is release.
//  A live callback for when the slider value is changed.
// The getValue() method provides the slider value.
//

#ifndef SDL_SLIDER_H_
#define SDL_SLIDER_H_

#include <SDL2/SDL.h>

#include "sdl-widget.h"

class SdlSlider : public SdlWidget
{
	double percent;

	void (*liveCallback)(SDL_Event&,WidgetReference);

	ImageReference createSliderBackground();

public:
	SdlSlider(SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference));
	SdlSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference));
	SdlSlider(SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference), void (*)(SDL_Event&, WidgetReference));
	SdlSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference), void (*)(SDL_Event&, WidgetReference));
	~SdlSlider();

	void handleEvent(SDL_Event & event);

	double getValue() { return percent; }
};

typedef SdlSlider * SliderReference;

#endif
