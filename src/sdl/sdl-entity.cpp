
#include <iostream>

#include "sdl-entity.h"

const SDL_Rect * SdlEntity::mapRect = 0;
int SdlEntity::worldSize = 0;

SdlEntity::SdlEntity(const Entity & entity) :
	SdlWidget(WL_NON_INTERACTIVE),
	entity(&entity)
{
	std::cout << "SdlEntity::SdlEntity(const Entity&)" << std::endl;

	size = mapRect->w / worldSize;

	Color color;
	switch(entity.getFaction())
	{
		case FT_STATIC:
			color = C_GRAY;
			break;

		case FT_ANIMAL_DOMESTIC:
			color = C_CYAN;
			break;

		case FT_ANIMAL_PASSIVE:
			color = C_YELLOW;
			break;

		case FT_ANIMAL_HOSTILE:
			color = C_MAGENTA;
			break;

		case FT_PLAYER_1:
			color = C_BLUE;
			break;

		case FT_PLAYER_2:
			color = C_RED;
			break;

		default:
			color = C_BLACK;
			break;
	}

	surface = sdlUtility.createCircle(color, size);

	clipping.x = 0;
	clipping.y = 0;
	clipping.w = size;
	clipping.h = size;

	updatePosition();

	state = WS_HIDDEN;
}

void SdlEntity::updatePosition()
{
	boundingBox.x = mapRect->x + entity->getPosition().x * size;
	boundingBox.y = mapRect->y + entity->getPosition().y * size;
	boundingBox.w = size;
	boundingBox.h = size;
}

void SdlEntity::update()
{
	updatePosition();
}
