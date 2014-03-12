
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "config.h"
#include "sdl-manager.h"

enum {
	MM_NEW_GAME,
	MM_SHOW_CREDITS,
	MM_QUIT_GAME,

	MM_COUNT
};

enum GameMode {
	GM_ERROR,
	GM_MENU,
	GM_RUNNING,
	GM_QUIT
};

class GameManager : public Config
{
	static GameManager * self;
	static GameMode mode;

	ButtonReference button[MM_COUNT];

	WidgetReference mapView;

	int targetButtonIndex;
	std::string targetButtonLabel;
	void (*targetButtonCallback) (SDL_Event&);
	SDL_Rect rect;

	static void newGame(SDL_Event & event);
	static void showCredits(SDL_Event & event);
	static void quitGame(SDL_Event & event);

	// From Config
	bool setProperty(std::string property, std::string value);
	bool setProperty(std::string property, int value);
	bool setProperty(std::string property, int value1, int value2);

public:
	GameManager();
};

#endif
