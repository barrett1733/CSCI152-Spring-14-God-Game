//
//  File: sdl-text-display.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Text Display Widget Definition
// Extends the generic Widget Class.
// Simply display a string of text.
// Text can be changed via setText() method.
//

#ifndef SDL_TEXT_DISPLAY_H_
#define SDL_TEXT_DISPLAY_H_

#include "sdl-widget.h"
#include <SDL2_ttf/SDL_ttf.h>

#include <string>

class SdlTextDisplay : public SdlWidget
{
	TTF_Font * font;
	SDL_Color color;
	Color backgroundColor;
	std::string text;
	FontSize fontSize;

	void buildSurface();

public:
	SdlTextDisplay(SDL_Surface * surface_arg, SDL_Rect & rect, std::string text_arg);
	SdlTextDisplay(std::string text_arg, SDL_Rect & rect);
	SdlTextDisplay(std::string text_arg, SDL_Rect & rect, Color colorBackground, FontSize fontSize);
	SdlTextDisplay(int xPos, int yPos, int width, int height);
	~SdlTextDisplay();

	void setText(std::string text_arg);
};

typedef SdlTextDisplay * TextDisplayReference;

#endif
