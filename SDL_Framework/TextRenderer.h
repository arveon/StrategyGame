#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "sdl_manager.h"

#pragma once
///Class can be used as both a display for text to be drawn allowing to change the text rendered whenever required
///and as a container for static functions that allow to render text onto textures
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
	static SDL_Texture* get_texture_from_text(TTF_Font* font, std::string caption,  SDL_Color clr);
	static SDL_Texture* get_texture_from_text(std::string font_path, int size, std::string caption,  SDL_Color clr);

	TextRenderer(TTF_Font*, SDL_Color, std::string, int x = 0, int y = 0);
	TextRenderer();
	~TextRenderer();
};

