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
	static SDL_Texture* get_texture_from_text(TTF_Font* font, std::string caption, SDL_Renderer* renderer, SDL_Color clr);
	static SDL_Texture* get_texture_from_text(std::string font_path, int size, std::string caption, SDL_Renderer* renderer, SDL_Color clr);

	TextRenderer(TTF_Font*, SDL_Color, std::string);
	~TextRenderer();
};

