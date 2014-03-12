
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

	load("main-menu.cfg");

	sdl.launchWindow("Window Title!", 800, 600);
	sdl.subscribeToEvent(quitGame, SDL_QUIT);
	sdl.subscribeToEvent(quitGame, SDL_KEYDOWN, '\033');

	mapView = new SdlMapView(200,0,600,600);
	mapView->hide();

	sdl.addWidget(mapView, WL_BACKGROUND);

	// While application is running
	std::cout << "Starting Game Loop" << std::endl;
	while(mode != GM_QUIT)
	{
		sdl.update();
	}
}

void GameManager::newGame(SDL_Event & event)
{
	std::cout << "New Game" << std::endl;

	if(self->button[MM_NEW_GAME])
		self->button[MM_NEW_GAME]->hide();

	if(self->button[MM_SHOW_CREDITS])
		self->button[MM_SHOW_CREDITS]->hide();

	if(self->button[MM_QUIT_GAME])
		self->button[MM_QUIT_GAME]->moveTo(16,16);


	if(self->mapView)
		self->mapView->show();

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

// From Config
bool GameManager::setProperty(std::string property, std::string value)
{
	std::cout << "GameManager::SetProperty() : " << property << " = " << value << std::endl;
	if(property == "label")
	{
		targetButtonLabel = value;

		if(value == "New Game")
		{
			targetButtonIndex = MM_NEW_GAME;
			targetButtonCallback = newGame;
		}

		else if(value == "Show Credits")
		{
			targetButtonIndex = MM_SHOW_CREDITS;
			targetButtonCallback = showCredits;
		}

		else if(value == "Quit Game")
		{
			targetButtonIndex = MM_QUIT_GAME;
			targetButtonCallback = quitGame;
		}

		else
			return false;
	}
	else if(property == "action")
	{
		if(value == "create button")
		{
			std::cout << "createRect: " << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << std::endl;
			std::cout << "new SdlButton: " << targetButtonLabel << std::endl;
			button[targetButtonIndex] = new SdlButton(targetButtonLabel.c_str(), rect, targetButtonCallback);

			sdl.addWidget(button[targetButtonIndex], WL_INTERACTIVE);
		}
		else return false;
	}
	else
		return false;

	return true;
}

bool GameManager::setProperty(std::string property, int value)
{
	std::cout << "GameManager::SetProperty() : " << property << " = " << value << std::endl;
	return false;
}


bool GameManager::setProperty(std::string property, int value1, int value2)
{
	std::cout << "GameManager::SetProperty() : " << property << " = (" << value1 << ", " << value2 << ")" << std::endl;
	if(property == "position")
	{
		rect.x = value1;
		rect.y = value2;
		return true;
	}
	else if(property == "size")
	{
		rect.w = value1;
		rect.h = value2;
		return true;
	}
	return false;
}
