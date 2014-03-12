
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

	callbackMap["newGame()"]                = newGame;
	callbackMap["showCredits()"]            = showCredits;
	callbackMap["quitGame()"]               = quitGame;
	callbackMap["triangleSliderCallback()"] = triangleSliderCallback;
	callbackMap["sliderCallback()"]         = sliderCallback;

	buttonIndexMap["NEW_GAME"]              = MM_NEW_GAME;
	buttonIndexMap["SHOW_CREDITS"]          = MM_SHOW_CREDITS;
	buttonIndexMap["QUIT_GAME"]             = MM_QUIT_GAME;
	buttonIndexMap["TRIANGLE_SLIDER"]       = MM_TRIANGLE_SLIDER;
	buttonIndexMap["WORSHIP_SLIDER"]        = MM_WORSHIP_SLIDER;
	buttonIndexMap["MAP_VIEW"]              = MM_MAP_VIEW;

	for(widgetIndex = MM_ERROR; widgetIndex < MM_COUNT; widgetIndex ++)
		self->widgetList[widgetIndex] = 0;

	widgetIndex = MM_ERROR;
	callbackName = "";
	buttonConfig = 0;

	load("main-menu.cfg");

	sdl.launchWindow("Window Title!", 800, 600);
	sdl.subscribeToEvent(quitGame, SDL_QUIT);
	sdl.subscribeToEvent(quitGame, SDL_KEYDOWN, '\033');

	self->widgetList[MM_MAP_VIEW] = new SdlMapView(200,0,600,600);
	self->widgetList[MM_MAP_VIEW]->hide();
	sdl.addWidget(self->widgetList[MM_MAP_VIEW], WL_BACKGROUND);


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

	std::cout << "Hide Button: New Game " << self->widgetList[MM_NEW_GAME] << std::endl;
	if(self->widgetList[MM_NEW_GAME])
		self->widgetList[MM_NEW_GAME]->hide();

	std::cout << "Hide Button: Show Credits " << self->widgetList[MM_SHOW_CREDITS] << std::endl;
	if(self->widgetList[MM_SHOW_CREDITS])
		self->widgetList[MM_SHOW_CREDITS]->hide();

	std::cout << "Move Button: Quit Game " << self->widgetList[MM_QUIT_GAME] << std::endl;
	if(self->widgetList[MM_QUIT_GAME])
		self->widgetList[MM_QUIT_GAME]->moveTo(16,16);

	if(self->widgetList[MM_TRIANGLE_SLIDER])
		self->widgetList[MM_TRIANGLE_SLIDER]->show();

	if(self->widgetList[MM_WORSHIP_SLIDER])
		self->widgetList[MM_WORSHIP_SLIDER]->show();

	std::cout << "Show: Map View" << std::endl;
	if(self->widgetList[MM_MAP_VIEW])
		self->widgetList[MM_MAP_VIEW]->show();

	//mode = GM_QUIT;
}

void GameManager::showCredits(SDL_Event & event)
{
	std::cout << "Show Credits (NOT IMPLEMENTED - QUITING)" << std:: endl;
	mode = GM_QUIT;
}

void GameManager::quitGame(SDL_Event & event)
{
	std::cout << "Quit Game" << std::endl;
	mode = GM_QUIT;
}

void GameManager::sliderCallback(SDL_Event & event)
{
	double value = ((SliderReference) self->widgetList[MM_WORSHIP_SLIDER]) -> getValue();
	std::cout << "Slider Update: " << value << std::endl;
}
void GameManager::triangleSliderCallback(SDL_Event & event)
{
	double valueA = ((TriangleSliderReference) self->widgetList[MM_TRIANGLE_SLIDER]) -> getValueA();
	double valueB = ((TriangleSliderReference) self->widgetList[MM_TRIANGLE_SLIDER]) -> getValueB();
	double valueC = ((TriangleSliderReference) self->widgetList[MM_TRIANGLE_SLIDER]) -> getValueC();
	std::cout << "Triangle Update: " << valueA << ", " << valueB << ", " << valueC << std::endl;
}

// From Config
bool GameManager::setProperty(std::string property, std::string value)
{
	std::cout << "GameManager::SetProperty() : " << property << " = " << value << std::endl;

	if(property == "widget_id")
	{
		if(!buttonIndexMap[value])
			return false;
		widgetIndex = buttonIndexMap[value];
		buttonConfig |= BCFG_INDEX;
	}

	else if(property == "label")
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
		if(buttonConfig != BCFG_VALID)
		{
			std::cerr << "Invalid Button Configuration: " << buttonConfig << std::endl;
			if(! (buttonConfig & BCFG_INDEX)) std::cerr << "Missing index." << std::endl;
			if(! (buttonConfig & BCFG_LABEL)) std::cerr << "Missing label." << std::endl;
			if(! (buttonConfig & BCFG_CALLBACK)) std::cerr << "Missing callback." << std::endl;
			return false;
		}

		if(value == "button")
			widgetList[widgetIndex] = new SdlButton(buttonLabel.c_str(), rect, callbackMap[callbackName]);

		else if(value == "slider")
			widgetList[widgetIndex] = new SdlSlider(rect, callbackMap[callbackName]);

		else if(value == "triangle-slider")
			widgetList[widgetIndex] = new SdlTriangleSlider(rect, callbackMap[callbackName]);

		else return false;

		sdl.addWidget(widgetList[widgetIndex], WL_INTERACTIVE);
		buttonConfig = 0;
	}

	else if(property == "visibility")
	{
		if(value == "hidden")
		{
			widgetList[widgetIndex]->hide();
			std::cout << "Trying to hide: " << buttonLabel << " [" << widgetIndex << "]" << std::endl;
		}
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
