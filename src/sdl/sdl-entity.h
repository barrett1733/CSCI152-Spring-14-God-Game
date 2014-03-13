
#ifndef SDL_ENTITY_H_
#define SDL_ENTITY_H_

#include <iostream>

#include "sdl-widget.h"

class SdlEntity : public SdlWidget
{
public:
	SdlEntity(COLOR color, int width, int height);
	SdlEntity(ImageReference image, int width, int height);

	void handleEvent(SDL_Event & event)
	{
		updateState(event);
		if(state == WIDGET_HOVER)
			std::cout << "HI" << std::endl;
	}
};

typedef SdlEntity * EntityReference;

#endif
