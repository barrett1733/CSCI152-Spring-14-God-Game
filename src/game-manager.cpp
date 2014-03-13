
#include "game-manager.h"
#include "sdl/sdl-triangle-slider.h"
#include "sdl/sdl-map-view.h"

GameManager * GameManager::self = 0;
GameMode GameManager::mode = GM_ERROR;

void doNothing(SDL_Event & event, WidgetReference widget) {}

GameManager::GameManager()
{
	if(self)
		throw "GameManager already initialized";

	self = this;
	mode = GM_MENU;

	callbackMap["none"]                     = doNothing;
	callbackMap["newGame()"]                = newGame;
	callbackMap["pauseGame()"]              = pauseGame;
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

	sdl.launchWindow("Window Title!", 800, 600);
	sdl.subscribeToEvent(quitGame, SDL_QUIT);
	sdl.subscribeToEvent(quitGame, SDL_KEYDOWN, '\033');

	// While application is running
	std::cout << "Starting Game Loop" << std::endl;
	while(mode != GM_QUITING)
	{
		sdl.update();
	}
}

void GameManager::newGame(SDL_Event & event, WidgetReference widget)
{
	std::cout << "New Game" << std::endl;

	mode = GM_PLAYING;

	int widgetCount = self->widgetList.size();
	for(int widgetIndex = 0; widgetIndex < widgetCount; widgetIndex ++)
	{
		if(self->widgetList[widgetIndex]->mode & mode)
			self->widgetList[widgetIndex]->widget->show();
		else
			self->widgetList[widgetIndex]->widget->hide();
	}
}

void GameManager::pauseGame(SDL_Event & event, WidgetReference widget)
{
	std::cout << "Pause Game" << std::endl;

	mode = GM_PAUSING;

	int widgetCount = self->widgetList.size();
	for(int widgetIndex = 0; widgetIndex < widgetCount; widgetIndex ++)
	{
		if(self->widgetList[widgetIndex]->mode & mode)
			self->widgetList[widgetIndex]->widget->show();
		else
			self->widgetList[widgetIndex]->widget->hide();
	}
}

void GameManager::showCredits(SDL_Event & event, WidgetReference widget)
{
	std::cout << "Show Credits (NOT IMPLEMENTED - QUITING)" << std:: endl;
	mode = GM_QUITING;
}

void GameManager::quitGame(SDL_Event & event, WidgetReference widget)
{
	std::cout << "Quit Game (from button)" << std::endl;
	mode = GM_QUITING;
}

void GameManager::quitGame(SDL_Event & event)
{
	std::cout << "Quit Game" << std::endl;
	mode = GM_QUITING;
}

void GameManager::sliderCallback(SDL_Event & event, WidgetReference widget)
{
	// double value = ((SliderReference) self->widgetList[MM_WORSHIP_SLIDER]) -> getValue();
	// std::cout << "Slider Update: " << value << std::endl;
}
void GameManager::triangleSliderCallback(SDL_Event & event, WidgetReference widget)
{
	// double valueA = ((TriangleSliderReference) self->widgetList[MM_TRIANGLE_SLIDER]) -> getValueA();
	// double valueB = ((TriangleSliderReference) self->widgetList[MM_TRIANGLE_SLIDER]) -> getValueB();
	// double valueC = ((TriangleSliderReference) self->widgetList[MM_TRIANGLE_SLIDER]) -> getValueC();
	// std::cout << "Triangle Update: " << valueA << ", " << valueB << ", " << valueC << std::endl;
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
		if(!callbackMap[value])
			return false;
		callbackName = value;
		buttonConfig |= BCFG_CALLBACK;
	}

	else if(property == "create")
	{
		if( ! (buttonConfig & BCFG_VALID))
		{
			std::cerr << "\033[33mInvalid Button Configuration: " << buttonConfig << " != " << BCFG_VALID << "\033[m" << std::endl;
			if( ! (buttonConfig & BCFG_LABEL)) std::cerr << "Missing label." << std::endl;
			if( ! (buttonConfig & BCFG_CALLBACK)) std::cerr << "Missing callback." << std::endl;
			return false;
		}

		WidgetReference widget;
		int layer = WL_INTERACTIVE;

		if(value == "button")
			widget = new SdlButton(buttonLabel.c_str(), rect, callbackMap[callbackName]);

		else if(value == "slider")
			widget = new SdlSlider(rect, callbackMap[callbackName]);

		else if(value == "triangle-slider")
			widget = new SdlTriangleSlider(rect, callbackMap[callbackName]);

		else if(value == "map-view")
		{
			widget = new SdlMapView(rect.x, rect.y, rect.w, rect.h);
			layer = WL_BACKGROUND;
		}

		else return false;

		sdl.addWidget(widget, layer);
		widgetList.push_back(new GM_Widget(widget, buttonLabel));
		buttonConfig = 0;
	}

	else if(property == "initially")
	{
		if(value == "hidden")
		{
			widgetList.back()->widget->hide();
			std::cout << "Trying to hide: " << widgetList.back()->name << std::endl;
		}
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
