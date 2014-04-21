
#include <iostream>

#include "sdl-entity.h"

SdlMapView * SdlEntity::mapView = 0;
int SdlEntity::worldSize = 0;

SdlEntity::SdlEntity(const Entity & entity) :
	SdlWidget(WL_NON_INTERACTIVE),
	entity(&entity)
{
	size = mapView->getBoundingBox()->w / worldSize;

	Color color;
	switch(entity.getFaction())
	{
		case F_STATIC:
			switch(entity.getType())
			{
			case ET_TREE:
				color = C_GREEN;
				break;
			case ET_STONE:
				color = C_GRAY;
				break;
			case ET_IRON:
				color = C_BLACK;
				break;

			default:
				color = C_GRAY;
				break;
			}
			break;

		case F_ANIMAL_DOMESTIC:
			color = C_CYAN;
			break;

		case F_ANIMAL_PASSIVE:
			color = C_YELLOW;
			break;

		case F_ANIMAL_HOSTILE:
			color = C_MAGENTA;
			break;

		case F_PLAYER_1:
			color = C_BLUE;
			break;

		case F_PLAYER_2:
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
	boundingBox.w = size;
	boundingBox.h = size;

	updatePosition();

	state = WS_HIDDEN;
}

void SdlEntity::updatePosition()
{
	mapView->clear(boundingBox);

	boundingBox.x = entity->getPosition().getX() * size;
	boundingBox.y = entity->getPosition().getY() * size;

	mapView->draw(surface, boundingBox);
}

void SdlEntity::update()
{
	updatePosition();
}
