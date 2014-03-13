
#ifndef SDL_TEXT_DISPLAY_H_
#define SDL_TEXT_DISPLAY_H_

#include "sdl-widget.h"
#include <SDL2_ttf/SDL_ttf.h>

#include <string>

class SdlTextDisplay : public SdlWidget
{
	TTF_Font * font;
	SDL_Color color;
	std::string text;

	void buildSurface();

public:
	SdlTextDisplay(SDL_Surface * surface_arg, SDL_Rect & rect, std::string text_arg);
	~SdlTextDisplay();

	void setText(std::string text_arg);
};

typedef SdlTextDisplay * TextDisplayReference;

#endif
