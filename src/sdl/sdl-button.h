
#ifndef SDL_BUTTON_H_
#define SDL_BUTTON_H_

#include "sdl-widget.h"

class SdlButton : public SdlWidget
{
	ImageReference background;
	ImageReference createButtonBackground(SDL_Rect & rect);

	void setState(WidgetState);

public:
	SdlButton(SDL_Surface * surface, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference));
	SdlButton(const char * text, SDL_Rect & rect, void (*)(SDL_Event&, WidgetReference));
	~SdlButton();

	const SDL_Rect * getClipping();
	void handleEvent(SDL_Event & event);

	void setText(const char * text);
};

typedef SdlButton * ButtonReference;

#endif
