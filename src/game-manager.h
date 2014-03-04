
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "sdl-manager.h"

enum GameMode {
	GM_ERROR,
	GM_MENU,
	GM_RUNNING,
	GM_QUIT
};

class GameManager
{
	static GameMode mode;

	ButtonReference newGameButton;
	ButtonReference showCreditButton;
	ButtonReference quickButton;

	static void newGame(SDL_Event & event);
	static void showCredits(SDL_Event & event);
	static void quitGame(SDL_Event & event);

public:
	GameManager();
};

#endif