
#include "sdl-button.h"

SdlButton::SdlButton(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event)) :
	SdlWidgetBase(surface_arg, rect),
	callback(callback_arg)
{}

SdlButton::~SdlButton()
{
	callback = 0;
}

void SdlButton::handleEvent(SDL_Event & event)
{
	updateState(event);

	if(state == WIDGET_ON)
	{
		if(callback)
			callback(event);
		state = WIDGET_OFF;
	}

	// Update button appearance for button state
	clipping.y = boundingBox.h * state;
}
