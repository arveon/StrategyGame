#include <SDL.h>
#include <string>

#pragma once
class DialogWindow
{
private:
	std::string caption;
	SDL_Rect window;
	SDL_Texture* background;
public:
	DialogWindow();
	DialogWindow(SDL_Texture* bg);
	~DialogWindow();
};

