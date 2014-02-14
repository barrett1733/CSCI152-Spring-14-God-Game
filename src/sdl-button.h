#ifndef SDL_BUTTON_H_
#define SDL_BUTTON_H_

#include <SDL2/SDL.h>

#include <iostream>

#include "sdl-widget.h"

enum ButtonState { BUTTON_OFF, BUTTON_HOVER, BUTTON_ACTIVE, BUTTON_ON };

class SdlButton : public SdlWidget
{
	ButtonState state;
	void (*callback)();

public:
	SdlButton(SDL_Surface * surface, SDL_Rect & rect, void (*callback_arg)());
	~SdlButton();

	void handleEvent(SDL_Event & event);
};

typedef SdlButton * ButtonReference;

#endif
