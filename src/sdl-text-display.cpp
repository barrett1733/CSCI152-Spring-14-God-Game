
#include "sdl-text-display.h"

SdlTextDisplay::SdlTextDisplay(SDL_Surface * surface_arg, SDL_Rect & rect, std::string text_arg) :
	SdlWidget(surface_arg, rect, 0)
{
	text = text_arg;
	font = TTF_OpenFont( "res/arial.ttf", 16 );
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;

	buildSurface();
}

SdlTextDisplay::~SdlTextDisplay()
{
	TTF_CloseFont(font);
}

void SdlTextDisplay::setText(std::string text_arg)
{
	text = text_arg;
	buildSurface();
}

void SdlTextDisplay::buildSurface()
{
	// Clear the existing surface.
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

	if(text.length())
	{
		// Create a new text surface.
		SDL_Surface * textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

		// Blit the text surface onto the background and free the text surface
		SDL_BlitSurface(textSurface, NULL, surface, NULL);
		SDL_FreeSurface(textSurface);
	}
}
