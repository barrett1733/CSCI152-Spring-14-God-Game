//
//  File: sdl-widget.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Widget Definition
// The base class for all other widgets.
// Maintains an internal state, textures, bounding box, etc.
// Manages event handling (if a callback is provided).
//

#ifndef SDL_WIDGET_H_
#define SDL_WIDGET_H_

#include "sdl-utility.h"

enum WidgetLayer {
	WL_BACKGROUND,
	WL_NON_INTERACTIVE,
	WL_INTERACTIVE,

	WL_COUNT
};

enum WidgetState {
	WS_OFF,
	WS_HOVER,
	WS_ACTIVE,
	WS_ON,
	WS_DISABLED,
	WS_HIDDEN,

	WS_COUNT
};

class SdlWidget
{
protected:
	void (*callback)(SDL_Event & event, SdlWidget*);
	SDL_Surface * surface;
	SDL_Texture * texture;
	WidgetState state;
	SDL_Rect clipping;
	SDL_Rect boundingBox;

	WidgetLayer layer;

	void setClipping(const SDL_Rect&);
	void setBoundingBox(const SDL_Rect&);
	virtual void setState(WidgetState);
	void updateState(SDL_Event & event);

	virtual bool isInside(int xMouse, int yMouse);
public:
	SdlWidget();
	SdlWidget(WidgetLayer);
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect);
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event, SdlWidget*));

	virtual ~SdlWidget();


	SDL_Surface * getSurface();
	virtual const SDL_Rect * getClipping();
	virtual const SDL_Rect * getBoundingBox();
	void render(SDL_Renderer * renderer);
	void render(SDL_Texture * windowTexture);

	virtual void handleEvent(SDL_Event&);

	WidgetState getState();
	void disable();
	void enable();
	void hide();
	void show();

	void moveTo(int xPos, int yPos)
	{
		boundingBox.x = xPos;
		boundingBox.y = yPos;
	}

	int id;
};

typedef SdlWidget * WidgetReference;

#endif
