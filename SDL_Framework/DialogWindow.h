#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#pragma once
class DialogWindow
{
private:
	std::string caption;
	SDL_Texture* caption_text;
	SDL_Rect window;
	SDL_Texture* background;
public:
	DialogWindow();
	DialogWindow(SDL_Texture* bg);
	~DialogWindow();
};

