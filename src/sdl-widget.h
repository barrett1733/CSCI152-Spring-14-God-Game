
#ifndef SDL_WIDGET_H_
#define SDL_WIDGET_H_

#include <SDL2/SDL.h>

enum WidgetState {
	WIDGET_OFF,
	WIDGET_HOVER,
	WIDGET_ACTIVE,
	WIDGET_ON,
	WIDGET_DISABLED
};

class SdlWidget
{
protected:
	void (*callback)(SDL_Event & event);
	SDL_Surface * surface;
	WidgetState state;
	SDL_Rect clipping;
	SDL_Rect boundingBox;

	void updateState(SDL_Event & event);

	bool isInside(int xMouse, int yMouse);
public:
	SdlWidget();
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect);
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event));

	virtual ~SdlWidget();

	SDL_Surface * getSurface();
	const SDL_Rect * getClipping();
	const SDL_Rect * getBoundingBox();

	virtual void handleEvent(SDL_Event&);
};

typedef SdlWidget * WidgetReference;

#endif
