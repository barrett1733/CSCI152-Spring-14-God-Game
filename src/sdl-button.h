
#ifndef SDL_BUTTON_H_
#define SDL_BUTTON_H_

#include "sdl-widget.h"

class SdlButton : public SdlWidget
{
	ImageReference createButtonBackground(SDL_Rect & rect);

public:
	SdlButton(SDL_Surface * surface, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event));
	SdlButton(const char * text, SDL_Rect & rect, void (*)(SDL_Event&));
	~SdlButton();

	void handleEvent(SDL_Event & event);

	void setText(const char * text);
};

typedef SdlButton * ButtonReference;

#endif
