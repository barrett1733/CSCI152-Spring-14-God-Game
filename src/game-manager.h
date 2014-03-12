
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <vector>
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
	GM_ERROR   = 0x00,
	GM_MENU    = 0x01,
	GM_PLAYING = 0x02,
	GM_PAUSING = 0x04,
	GM_QUITING = 0x08,
};

enum {
	BCFG_LABEL = 0x01,
	BCFG_CALLBACK = 0x02,

	BCFG_VALID = BCFG_LABEL | BCFG_CALLBACK,
};

struct GM_Widget
{
	WidgetReference widget;
	std::string name;
	int mode;

	GM_Widget(WidgetReference reference, std::string label)
	{
		widget = reference;
		name = label;
		mode = 0;
	}
};

class GameManager : public Config
{
	static GameManager * self;
	static GameMode mode;

	std::map<std::string, void (*)(SDL_Event&)> callbackMap;
	std::map<std::string, GameMode> modeMap;

	std::vector<GM_Widget*> widgetList;

	SDL_Rect rect;
	std::string buttonLabel;
	std::string callbackName;
	int buttonConfig;

	static void newGame(SDL_Event & event);
	static void pauseGame(SDL_Event & event);
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
