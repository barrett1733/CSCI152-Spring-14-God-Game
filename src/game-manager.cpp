
#include "game-manager.h"

GameMode GameManager::mode = GM_ERROR;

GameManager::GameManager()
{
	mode = GM_MENU;

	sdl.launchWindow("Window Title!", 800, 600);
	sdl.subscribeToEvent(quitGame, SDL_QUIT);
	sdl.subscribeToEvent(quitGame, SDL_KEYDOWN, '\e');

	newGameButton     = sdl.createButton(newGame, 0, "New Game", 200, 100, 200, 50);
	showCreditsButton = sdl.createButton(showCredits, 0, "Credits", 200, 200, 200, 50);
	quickButton       = sdl.createButton(quitGame, 0, "Quit", 200, 300, 200, 50);

	newGameButton->disable();
	showCreditsButton->disable();

	// While application is running
	while(mode != GM_QUIT)
	{
		sdl.update();
	}
}

void GameManager::newGame(SDL_Event & event)
{
	std::cout << "New Game" << std::endl;
	mode = GM_QUIT;
}

void GameManager::showCredits(SDL_Event & event)
{
	std::cout << "Show Credits" << std:: endl;
	mode = GM_QUIT;
}

void GameManager::quitGame(SDL_Event & event)
{
	std::cout << "stop running" << std::endl;
	mode = GM_QUIT;
}
