
#ifndef SDL_EVENT_SUBSCRIBER_H_
#define SDL_EVENT_SUBSCRIBER_H_

#include <iostream>

struct SdlEventSubscriber
{
	void (*callback)();
	int type;
	int sym;

	SdlEventSubscriber();
	SdlEventSubscriber(void (*callback_arg)(), int type_arg, int sym_arg) :
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
				if(event.key.keysym.sym == sym)
					callback();
			}
			else
				callback();
		}
	} // end handleEvent()
};

typedef SdlEventSubscriber * SubscriptionReference;

#endif
