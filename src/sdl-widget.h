
#ifndef SDL_WIDGET_H_
#define SDL_WIDGET_H_

#include <SDL2/SDL.h>

enum WidgetState { WIDGET_OFF, WIDGET_HOVER, WIDGET_ACTIVE, WIDGET_ON };

class SdlWidgetBase
{
protected:
	WidgetState state;
	SDL_Surface * surface;
	SDL_Rect clipping;
	SDL_Rect boundingBox;

	void updateState(SDL_Event & event);

	bool isInside(int xMouse, int yMouse);
public:
	SdlWidgetBase(SDL_Surface * surface_arg, SDL_Rect & rect);

	virtual ~SdlWidgetBase();

	SDL_Surface * getSurface();
	const SDL_Rect * getClipping();
	const SDL_Rect * getBoundingBox();

	virtual void handleEvent(SDL_Event&) = 0;
};

typedef SdlWidgetBase * WidgetBaseReference;




class SdlWidget : public SdlWidgetBase
{
public:
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect) :
		SdlWidgetBase(surface_arg, rect)
	{}
	void handleEvent(SDL_Event&) {}
};

typedef SdlWidget * WidgetReference;

#endif
