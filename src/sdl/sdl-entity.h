
#ifndef SDL_ENTITY_H_
#define SDL_ENTITY_H_

#include <iostream>

#include "sdl-widget.h"
#include "../entity.h"

class SdlEntity : public SdlWidget
{
public:
	SdlEntity();
	SdlEntity(const Entity&);
	SdlEntity(EntityType, Position);
	SdlEntity(Color color, int size);
};

typedef SdlEntity * SdlEntityReference;

#endif
