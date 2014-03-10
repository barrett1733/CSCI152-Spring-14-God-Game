
#ifndef SDL_SLIDER_H_
#define SDL_SLIDER_H_

#include <SDL2/SDL.h>

#include "sdl-widget.h"

class SdlSlider : public SdlWidget
{
	double percent;

public:
	SdlSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event));
	~SdlSlider();

	void handleEvent(SDL_Event & event);

	double getValue() { return percent; }
};

typedef SdlSlider * SliderReference;

#endif
