
#include "game-manager.h"
#include "sdl-map-view.h"

GameManager * GameManager::self = 0;
GameMode GameManager::mode = GM_ERROR;

GameManager::GameManager()
{
	if(self)
		throw "GameManager already initialized";

	self = this;
	mode = GM_MENU;

	SDL_Rect rect;

	sdl.launchWindow("Window Title!", 800, 600);
	sdl.subscribeToEvent(quitGame, SDL_QUIT);
	sdl.subscribeToEvent(quitGame, SDL_KEYDOWN, '\e');


	rect = sdlUtility.createRect(200,100,200,50);
	newGameButton = new SdlButton("New Game", rect, newGame);

	rect = sdlUtility.createRect(200,200,200,50);
	showCreditsButton = new SdlButton("Credits", rect, showCredits);

	rect = sdlUtility.createRect(200,300,200,50);
	quitGameButton = new SdlButton("Quit", rect, quitGame);

	mapView = new SdlMapView(200,0,600,600);

	sdl.addWidget(newGameButton, WL_INTERACTIVE);
	sdl.addWidget(showCreditsButton, WL_INTERACTIVE);
	sdl.addWidget(quitGameButton, WL_INTERACTIVE);
	sdl.addWidget(mapView, WL_BACKGROUND);

	// While application is running
	while(mode != GM_QUIT)
	{
		sdl.update();
	}
}

void GameManager::newGame(SDL_Event & event)
{
	std::cout << "New Game" << std::endl;
	self->newGameButton->hide();
	self->showCreditsButton->hide();
	self->quitGameButton->moveTo(16,16);
	//mode = GM_QUIT;
}

void GameManager::showCredits(SDL_Event & event)
{
	std::cout << "Show Credits" << std:: endl;
	mode = GM_QUIT;
}

void GameManager::quitGame(SDL_Event & event)
{
	std::cout << "Quit Game" << std::endl;
	mode = GM_QUIT;
}
