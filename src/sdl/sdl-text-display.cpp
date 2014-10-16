//
//  File: sdl-text-display.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Text Display Widget Implementation
//

#include <iostream>

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

SdlTextDisplay::SdlTextDisplay(std::string text_arg, SDL_Rect & rect) :
	SdlWidget(0, rect, 0)
{
	surface = sdlUtility.createSurface(rect.w, rect.h);
	text = text_arg;
	font = TTF_OpenFont( "res/arial.ttf", 16 );
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;

	buildSurface();
}

SdlTextDisplay::SdlTextDisplay(int xPos, int yPos, int width, int height) :
	SdlWidget()
{
	clipping = sdlUtility.createRect(0, 0, width, height);
	boundingBox = sdlUtility.createRect(xPos, yPos, width, height);
	surface = sdlUtility.createSurface(width, height);
	text = "";
	font = TTF_OpenFont( "res/arial.ttf", 16 );
	if(!font)
		std::cerr << TTF_GetError() << std::endl;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;

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
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 255, 0));

	if(text.length())
	{
		// Create a new text surface.
		SDL_Surface * textSurface = TTF_RenderText_Blended(font, text.c_str(), color);

		// Blit the text surface onto the background and free the text surface
		SDL_BlitSurface(textSurface, NULL, surface, NULL);
		SDL_FreeSurface(textSurface);
	}

	if(texture) SDL_DestroyTexture(texture);
	texture = 0;
}
