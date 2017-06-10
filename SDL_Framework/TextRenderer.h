#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "sdl_manager.h"

#pragma once
class TextRenderer
{
private:
	TTF_Font* font;
	SDL_Rect draw_rect;
	SDL_Color draw_color;

	std::string text;

	SDL_Texture* text_texture;
public:
	void draw(SDL_Renderer*);
	void change_caption(std::string new_text);
	TextRenderer(TTF_Font*, SDL_Color, std::string);
	~TextRenderer();
};

