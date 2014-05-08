//
//  File: sdl-event-subscriber.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Event Subscriber Definition
// Provides an interface to invoke a specified callback.
// Requires a fully qualified SDL_Event to instantiate.
//

#ifndef SDL_EVENT_SUBSCRIBER_H_
#define SDL_EVENT_SUBSCRIBER_H_

#include <iostream>

struct SdlEventSubscriber
{
	void (*callback)(SDL_Event&);
	unsigned int type;
	int sym;

	SdlEventSubscriber();
	SdlEventSubscriber(void (*callback_arg)(SDL_Event&), unsigned int type_arg, int sym_arg) :
		callback(callback_arg),
		type(type_arg),
		sym(sym_arg)
	{}

	void handleEvent(SDL_Event & event)
	{
		if(callback && event.type == type)
		{
			if(type == SDL_KEYDOWN || type == SDL_KEYUP)
			{
				if(sym == SDLK_UNKNOWN || event.key.keysym.sym == sym)
					callback(event);
			}
			else
				callback(event);
		}
	} // end handleEvent()
};

typedef SdlEventSubscriber * SubscriptionReference;

#endif
