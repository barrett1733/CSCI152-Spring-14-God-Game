
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <map>

#include "config.h"
#include "sdl-manager.h"
#include "sdl-triangle-slider.h"

enum {
	// MAIN MENU BUTTONS
	MM_ERROR,
	MM_NEW_GAME,
	MM_SHOW_CREDITS,
	MM_QUIT_GAME,

	// GAMEPLAY WIDGETS
	MM_TRIANGLE_SLIDER,
	MM_WORSHIP_SLIDER,
	MM_MAP_VIEW,

	// TOTAL NUMBER OF STATIC WIDGETS
	MM_COUNT
};

enum GameMode {
	GM_ERROR,
	GM_MENU,
	GM_PLAYING,
	GM_PAUSING,
	GM_QUITING
};

enum {
	BCFG_INDEX = 0x01,
	BCFG_LABEL = 0x02,
	BCFG_CALLBACK = 0x04,

	BCFG_VALID = 0x07,
};

class GameManager : public Config
{
	static GameManager * self;
	static GameMode mode;

	std::map<std::string, void (*)(SDL_Event&)> callbackMap;
	std::map<std::string, int> buttonIndexMap;
	std::map<std::string, GameMode> gameModeMap;

	WidgetReference widgetList[MM_COUNT];

	SDL_Rect rect;
	int widgetIndex;
	std::string buttonLabel;
	std::string callbackName;
	int buttonConfig;

	static void newGame(SDL_Event & event);
	static void showCredits(SDL_Event & event);
	static void quitGame(SDL_Event & event);
	static void sliderCallback(SDL_Event & event);
	static void triangleSliderCallback(SDL_Event & event);

	// From Config
	bool setProperty(std::string property, std::string value);
	bool setProperty(std::string property, int value);
	bool setProperty(std::string property, int value1, int value2);

public:
	GameManager();
};

#endif
