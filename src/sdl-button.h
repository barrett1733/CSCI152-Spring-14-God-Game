
#ifndef SDL_BUTTON_H_
#define SDL_BUTTON_H_

#include "sdl-widget.h"

class SdlButton : public SdlWidget
{

public:
	SdlButton(SDL_Surface * surface, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event));
	~SdlButton();

	void handleEvent(SDL_Event & event);
};

typedef SdlButton * ButtonReference;

#endif
