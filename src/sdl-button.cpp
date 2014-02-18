
#include "sdl-button.h"

SdlButton::SdlButton(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event)) :
	SdlWidgetBase(surface_arg, rect),
	state(BUTTON_OFF),
	callback(callback_arg)
{}

SdlButton::~SdlButton()
{
	state = BUTTON_OFF;
	callback = 0;
}

void SdlButton::handleEvent(SDL_Event & event)
{
	//If mouse event happened
	if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int xMouse, yMouse;
		SDL_GetMouseState( &xMouse, &yMouse );

		//Check if mouse is in button
		bool inside = isInside(xMouse, yMouse);

		//Mouse is outside button
		if( !inside )
			state = BUTTON_OFF;

		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( event.type )
			{
				case SDL_MOUSEMOTION:
				if(state == BUTTON_OFF)
					state = BUTTON_HOVER;
				break;

				case SDL_MOUSEBUTTONDOWN:
				state = BUTTON_ACTIVE;
				break;

				case SDL_MOUSEBUTTONUP:
				if(state == BUTTON_ACTIVE)
				{
					state = BUTTON_ON;
					if(callback)
						callback(event);
					else
						std::cout << "Button clicked without callback!" << std::endl;
					state = BUTTON_OFF;
				}
				break;
			}
		}
	}

	// Update button appearance for button state
	clipping.y = boundingBox.h * state;
}
