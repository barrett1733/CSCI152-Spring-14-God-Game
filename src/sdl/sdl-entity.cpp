
#include <iostream>

#include "sdl-entity.h"

SdlEntity::SdlEntity(COLOR color, int size) : SdlWidget()
{
	surface = sdlUtility.createCircle(color, size);

	clipping.w = size;
	clipping.h = size;
	boundingBox.w = size;
	boundingBox.h = size;

	std::cout << "SDL Entity created." << std::endl;
}
