//
//  File: game-manager.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Game Manager Implementation
//

#include "game-manager.h"
#include "sdl/sdl-triangle-slider.h"
#include "sdl/sdl-map-view.h"

GameManager * GameManager::self = 0;
GameMode GameManager::mode_ = GM_ERROR;

void doNothing(SDL_Event & event, WidgetReference widget) {}

GameManager::GameManager()
{
	if(self)
		throw "GameManager already initialized";

	self = this;
	mode_ = GM_MENU;

	callbackMap["none"]                     = doNothing;
	callbackMap["newGame()"]                = newGame;
	callbackMap["pauseGame()"]              = pauseGame;
	callbackMap["unpauseGame()"]            = unpauseGame;
	callbackMap["showCredits()"]            = showCredits;
	callbackMap["quitGame()"]               = quitGame;
	callbackMap["triangleSliderCallback()"] = triangleSliderCallback;
	callbackMap["sliderCallback()"]         = sliderCallback;

	modeMap["loading"] = GM_MENU;
	modeMap["playing"] = GM_PLAYING;
	modeMap["pausing"] = GM_PAUSING;

	callbackName = "";
	buttonConfig = 0;

	load("res/main-menu.cfg");


	sdl.subscribeToEvent(quitGame, SDL_QUIT);
	sdl.subscribeToEvent(quitGame, SDL_KEYDOWN, '\033');
}

void GameManager::setGameState(GameState state)
{
	if(mode_ == state) return;

	mode_ = state;
	unsigned long widgetCount = self->widgetList.size();
	for(unsigned long widgetIndex = 0; widgetIndex < widgetCount; widgetIndex ++)
	{
		if(self->widgetList[widgetIndex]->mode & mode_)
			self->widgetList[widgetIndex]->widget->show();
		else
			self->widgetList[widgetIndex]->widget->hide();
	}
}

void GameManager::newGame(SDL_Event & event, WidgetReference widget)
{
	std::cout << "New Game" << std::endl;
	setGameState(GM_PLAYING);
}

void GameManager::pauseGame(SDL_Event & event, WidgetReference widget)
{
	std::cout << "Pause Game" << std::endl;
	setGameState(GM_PAUSING);
}

void GameManager::unpauseGame(SDL_Event & event, WidgetReference widget)
{
	std::cout << "Unpause Game" << std::endl;
	setGameState(GM_PLAYING);
}

void GameManager::showCredits(SDL_Event & event, WidgetReference widget)
{
	std::cout << "Show Credits (NOT IMPLEMENTED - QUITING)" << std:: endl;
	mode_ = GM_QUITTING;
}

void GameManager::quitGame(SDL_Event & event, WidgetReference widget)
{
	std::cout << "Quit Game (from button)" << std::endl;
	mode_ = GM_QUITTING;
}

void GameManager::quitGame(SDL_Event & event)
{
	std::cout << "Quit Game" << std::endl;
	mode_ = GM_QUITTING;
}

void GameManager::sliderCallback(SDL_Event & event, WidgetReference widget)
{
	// double value = ((SliderReference) widget) -> getValue();
	// Commented out for MAX fps
	//std::cout << "Slider Update: " << value << std::endl;
}

void GameManager::triangleSliderCallback(SDL_Event & event, WidgetReference widget)
{
	// double valueA = ((TriangleSliderReference) widget)-> getValueA();
	// double valueB = ((TriangleSliderReference) widget)-> getValueB();
	// double valueC = ((TriangleSliderReference) widget)-> getValueC();
	// Commented out for MAX fps
	//std::cout << "Triangle Update: " << valueA << ", " << valueB << ", " << valueC << std::endl;
}

// From Config
bool GameManager::setProperty(std::string property, std::string value)
{

	if(property == "label")
	{
		buttonLabel = value;
		buttonConfig |= BCFG_LABEL;
	}

	else if(property == "callback")
	{
		callbackName = "none";
		if(!callbackMap[value])
			return false;
		callbackName = value;
		buttonConfig |= BCFG_CALLBACK;
	}

	else if(property == "create")
	{
		if( ! (buttonConfig & BCFG_VALID))
		{
			std::cerr << "\033[33m Invalid Button Configuration: " << buttonConfig << " != " << BCFG_VALID << "\033[m" << std::endl;
			if( ! (buttonConfig & BCFG_LABEL)) std::cerr << "Missing label." << std::endl;
			if( ! (buttonConfig & BCFG_CALLBACK)) std::cerr << "Missing callback." << std::endl;
			return false;
		}

		WidgetReference widget;

		if(value == "button")
			widget = new SdlButton(buttonLabel.c_str(), rect, callbackMap[callbackName]);

		else if(value == "slider")
			widget = new SdlSlider(rect, callbackMap[callbackName]);

		else if(value == "triangle-slider")
			widget = new SdlTriangleSlider(rect, callbackMap[callbackName]);

		else return false;

		widgetList.push_back(new GM_Widget(widget, buttonLabel));
		buttonConfig = 0;
	}

	else if(property == "initially")
	{
		if(value == "hidden")
			widgetList.back()->widget->hide();
	}

	else if(property == "show_when")
	{
		if(!modeMap[value])
			return false;
		widgetList.back()->mode |= modeMap[value];
	}

	else return false;

	return true;
}

bool GameManager::setProperty(std::string property, int value)
{
	std::cout << "GameManager::SetProperty() : " << property << " = " << value << std::endl;
	return false;
}

bool GameManager::setProperty(std::string property, int value1, int value2)
{
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
