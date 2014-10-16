//
//  File: sdl-button.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Button Widget Class Definition
// Extends the generic Widget Class.
// Renders as a clickable rectangle.
// Successfully 'clicking' the button will invoke the callback.
//

#ifndef SDL_BUTTON_H_
#define SDL_BUTTON_H_

#include "sdl-widget.h"

class SdlButton : public SdlWidget
{
	ImageReference background;
	ImageReference createButtonBackground(SDL_Rect & rect);
	FontSize fontSize;

	void setState(WidgetState);

public:
	SdlButton(SDL_Surface * surface, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference));
	SdlButton(const char * text, FontSize, SDL_Rect & rect, void (*)(SDL_Event&, WidgetReference));
	SdlButton(const char * text, SDL_Rect & rect, void (*)(SDL_Event&, WidgetReference));
	~SdlButton();

	const SDL_Rect * getClipping();
	void handleEvent(SDL_Event & event);

	void setText(const char * text);
};

typedef SdlButton * ButtonReference;

#endif
