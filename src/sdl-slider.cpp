
#include "sdl-slider.h"

SdlSlider::SdlSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event)) :
	SdlWidget(surface_arg, rect, callback_arg),
	percent(0)
{
	clipping.x = clipping.w - clipping.h / 2;
}

SdlSlider::~SdlSlider()
{
	percent = 0;
}

void SdlSlider::handleEvent(SDL_Event & event)
{

	updateState(event);

	if(state == WIDGET_ACTIVE)
	{
		int xMouse, yMouse;
		SDL_GetMouseState( &xMouse, &yMouse );

		double previous = percent;
		int handleWidth = clipping.h / 2;

		percent = (xMouse - boundingBox.x)/(float)boundingBox.w;
		if(percent < 0) percent = 0;
		if(percent > 1) percent = 1;

		clipping.x = (clipping.w - handleWidth) * (1-percent);

		if(percent != previous && callback)
			callback(event);
	}

	if(state == WIDGET_ON)
	{
		state = WIDGET_OFF;
		if(callback)
			callback(event);
	}
}
