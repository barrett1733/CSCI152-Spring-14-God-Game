//
//  File: sdl-button.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Button Widget Implementation
//

#include "sdl-button.h"

SdlButton::SdlButton(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(surface_arg, rect, callback_arg),
	fontSize(16)
{
	SDL_BlitSurface(surface, NULL, background, NULL);
}

SdlButton::SdlButton(const char * text, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(0, rect, callback_arg),
	fontSize(16)
{
	surface = sdlUtility.createSurface(rect.w, WS_COUNT * rect.h);
	background = createButtonBackground(rect);
	setText(text);
}

SdlButton::SdlButton(const char * text, FontSize fontSize, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(0, rect, callback_arg),
	fontSize(fontSize)
{
	surface = sdlUtility.createSurface(rect.w, WS_COUNT * rect.h);
	background = createButtonBackground(rect);
	setText(text);
}

SdlButton::~SdlButton()
{}

void SdlButton::setState(WidgetState state)
{
	SdlWidget::setState(state);
	clipping.y = boundingBox.h * state;
}

const SDL_Rect * SdlButton::getClipping()
{
	clipping.y = boundingBox.h * state;
	return & clipping;
}
void SdlButton::handleEvent(SDL_Event & event)
{
	updateState(event);

	if(state == WS_ON)
	{
		setState(WS_OFF);
		if(callback)
			callback(event, this);
	}
}

ImageReference SdlButton::createButtonBackground(SDL_Rect & rect)
{
	int width = rect.w;
	int height = rect.h;
	SDL_Rect clip;

	ImageReference image = sdlUtility.createSurface(width, WS_COUNT * height);
	SDL_FillRect(image, NULL, sdlUtility.getColor(image,C_BLACK));

	ImageReference buttonFill = sdlUtility.createSurface(width, height);
	SDL_PixelFormat * pixelFormat = buttonFill->format;

	for(int i = 0; i < WS_COUNT; i++)
	{
		int tone = 32 * (WS_COUNT-i);
		SDL_FillRect(buttonFill, NULL, SDL_MapRGBA(pixelFormat, tone, tone, tone, 255));
		rect = sdlUtility.createRect(1, 1,            width-2, height-2);
		clip = sdlUtility.createRect(1, 1 + i*height, width-2, height-2);
		SDL_BlitSurface(buttonFill, &rect, image, &clip);
	}
	SDL_FreeSurface(buttonFill);

	return image;
}

void SdlButton::setText(const char * text)
{
	int width = boundingBox.w;
	int height = boundingBox.h;

	SDL_Rect rect;
	SDL_Rect clip;

	SDL_BlitSurface(background, NULL, surface, NULL);
	SDL_Surface * textSurface = sdlUtility.createTextSurface(text, fontSize);

	int yPosText = (height - textSurface->h)/2;
	int xPosText = (width - textSurface->w)/2;
	if(xPosText < 8) xPosText = 8;

	for(int i = 0; i < WS_COUNT; i++)
	{
		rect = sdlUtility.createRect(xPosText, yPosText, width, height);
		clip = sdlUtility.createRect(xPosText, yPosText + i*height, width, height );
		SDL_BlitSurface(textSurface, NULL, surface, &clip);
	}
	SDL_FreeSurface(textSurface);

	if(texture) SDL_DestroyTexture(texture);
	texture = 0;
}
