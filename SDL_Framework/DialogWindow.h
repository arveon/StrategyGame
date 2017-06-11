#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "TextRenderer.h"
#include "sdl_manager.h"

#pragma once
class dialog_window
{
protected:
	std::string caption;
	SDL_Texture* caption_text;
	SDL_Rect window;
	SDL_Texture* background;
public:
	dialog_window();
	dialog_window(SDL_Texture* bg, SDL_Point window_center, bool is_modal, std::string text, int width, int height);
	~dialog_window();
};

