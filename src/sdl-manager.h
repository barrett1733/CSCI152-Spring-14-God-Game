
#ifndef SDL_MANAGER_H_
#define SDL_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>

#include <iostream>

class SdlManager
{

public:

	SDL_Window * window;
	SDL_Renderer* renderer = NULL;
	SDL_Surface * surface;

	SdlManager();
	~SdlManager();

	void launchWindow(const char * title, int width, int height);

	SDL_Texture * loadTexture( const char * file );

	void renderTexture(SDL_Texture *texture, int x, int y);
	void drawImage(SDL_Texture *texture, int x, int y);


	void test()
	{
		launchWindow("Window Title!", 1024, 768);

		SDL_Texture * my_dot  = loadTexture("res/dot.bmp");

		// dot position and size
		float xPos, yPos;
		xPos = 400;
		yPos = 300;
		SDL_Rect dotBox;
		dotBox.w = 8;
		dotBox.h = 8;

		//Main loop flag
		bool quit = false;

		// dot velocity
		float velocityIncrement = 0.1;
		float xVel, yVel;
		xVel = 0;
		yVel = 0;

		//Event handler
		SDL_Event e;

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				switch(e.type)
				{
					case SDL_KEYDOWN:
						switch(e.key.keysym.sym)
						{
							case SDLK_UP: yVel -= velocityIncrement; break;
							case SDLK_DOWN: yVel += velocityIncrement; break;
							case SDLK_LEFT: xVel -= velocityIncrement; break;
							case SDLK_RIGHT: xVel += velocityIncrement; break;
						}
						break;

					case SDL_QUIT:
						quit = true;
						break;

				}
			}

			xPos += xVel;
			yPos += yVel;

			if(xPos < 0)    xPos = 1023;
			if(xPos > 1023) xPos = 0;
			if(yPos < 0)    yPos = 767;
			if(yPos > 767)  yPos = 0;


			//Clear screen
			SDL_RenderClear( renderer );

			//Render texture to screen
			dotBox.x = xPos;
			dotBox.y = yPos;
			SDL_RenderCopy( renderer, my_dot, NULL, &dotBox );

			//Update screen
			SDL_RenderPresent( renderer );
		}

	}
};

#endif

extern SdlManager sdl;
