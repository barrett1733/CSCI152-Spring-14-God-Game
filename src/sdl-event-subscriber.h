
#ifndef SDL_EVENT_SUBSCRIBER_H_
#define SDL_EVENT_SUBSCRIBER_H_

#include <iostream>

struct SdlEventSubscriber
{
	void (*callback)(SDL_Event & event);
	int type;
	int sym;

	SdlEventSubscriber();
	SdlEventSubscriber(void (*callback_arg)(SDL_Event & event), int type_arg, int sym_arg) :
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
