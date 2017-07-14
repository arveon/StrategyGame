#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "TextRenderer.h"
#include "sdl_manager.h"

#pragma once
///Parent class of all the dialog windows
///Contains the basic information like text, bg, draw rectangle and draw logic for them
class dialog_window
{
protected:
	std::string caption;
	SDL_Texture* caption_text;
	SDL_Rect window;
	SDL_Texture* background;
	SDL_Color text_color;

	void draw(SDL_Renderer* renderer);

public:
	dialog_window(SDL_Texture* bg, SDL_Point window_pos, bool is_modal, std::string text, int width, int height);
	~dialog_window();
};

