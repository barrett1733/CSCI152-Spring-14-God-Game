
#ifndef SDL_ENTITY_H_
#define SDL_ENTITY_H_

#include <iostream>

#include "sdl-widget.h"

class SdlEntity : public SdlWidget
{
public:
	SdlEntity(COLOR color, int size);
	SdlEntity();
};

typedef SdlEntity * EntityReference;

#endif
