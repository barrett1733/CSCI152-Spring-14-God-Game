
#ifndef SDL_WIDGET_H_
#define SDL_WIDGET_H_

#include "sdl-utility.h"

enum {
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

	void setClipping(const SDL_Rect&);
	void setBoundingBox(const SDL_Rect&);
	virtual void setState(WidgetState);
	void updateState(SDL_Event & event);

	virtual bool isInside(int xMouse, int yMouse);
public:
	SdlWidget();
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect);
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event, SdlWidget*));

	virtual ~SdlWidget();


	SDL_Surface * getSurface();
	virtual const SDL_Rect * getClipping();
	virtual const SDL_Rect * getBoundingBox();
	void render(SDL_Renderer * renderer);

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
};

typedef SdlWidget * WidgetReference;

#endif
