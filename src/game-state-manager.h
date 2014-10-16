//
//  File: game-manager.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Game Manager Definition
// Implements the Config interface.
// This is a singleton class.
// Maintains the game state.
// Provides the main menu (new game, etc), and the pause button.
//

#ifndef GAME_STATE_MANAGER_H_
#define GAME_STATE_MANAGER_H_

#include <vector>
#include <map>

#include "config.h"
#include "sdl/sdl-manager.h"

enum GameMode {
	GM_ERROR   = 0x00,
	GM_MENU    = 0x01,
	GM_PLAYING = 0x02,
	GM_PAUSING = 0x04,
	GM_QUITTING = 0x08,
};

typedef GameMode GameState;

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

class GameStateManager : public Config
{
	static GameStateManager * self;
	static GameMode mode_;

	std::map<std::string, void (*)(SDL_Event&, WidgetReference)> callbackMap;
	std::map<std::string, GameMode> modeMap;

	std::vector<GM_Widget*> widgetList;

	SDL_Rect rect;
	std::string buttonLabel;
	std::string callbackName;
	int buttonConfig;

	static void setGameState(GameState);

	static void newGame(SDL_Event & event, WidgetReference);
	static void pauseGame(SDL_Event & event, WidgetReference);
	static void unpauseGame(SDL_Event & event, WidgetReference);
	static void showCredits(SDL_Event & event, WidgetReference);
	static void quitGame(SDL_Event & event);
	static void quitGame(SDL_Event & event, WidgetReference);
	static void sliderCallback(SDL_Event & event, WidgetReference widget);
	static void triangleSliderCallback(SDL_Event & event, WidgetReference widget);

	// From Config
	bool setProperty(std::string property, std::string value);
	bool setProperty(std::string property, int value);
	bool setProperty(std::string property, int value1, int value2);

public:
	GameStateManager();

	GameMode mode() { return mode_; }
};

#endif
