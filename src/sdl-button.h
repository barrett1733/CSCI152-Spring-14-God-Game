#ifndef SDL_BUTTON_H_
#define SDL_BUTTON_H_

#include <SDL2/SDL.h>

#include <iostream>

#include "sdl-widget.h"

enum ButtonState { BUTTON_OFF, BUTTON_HOVER, BUTTON_ACTIVE, BUTTON_ON };

class SdlButton : public SdlWidgetBase
{
	ButtonState state;
	void (*callback)(SDL_Event & event);

public:
	SdlButton(SDL_Surface * surface, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event));
	~SdlButton();

	void handleEvent(SDL_Event & event);
};

typedef SdlButton * ButtonReference;

#endif
