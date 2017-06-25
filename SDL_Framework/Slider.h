#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextRenderer.h"
#include "Mouse.h"
#include "Constants.h"
class slider
{
private:
	SDL_Texture* bar_texture;
	SDL_Texture* slider_texture;
	SDL_Texture* title_texture;

	SDL_Rect element_draw_rect;
	SDL_Rect title_draw_rect;
	SDL_Rect slider_draw_rect;
	int cur_value;
public:
	slider();
	slider(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* bar, SDL_Texture* slider, SDL_Rect draw_rect, int value = 0, std::string title = "default slider");
	slider(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* bar, SDL_Texture* slider, int w, int h, int x, int y, int value = 0, std::string title = "default slider");
	slider(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* bar, SDL_Texture* slider, int w, int h, SDL_Point pos, int value = 0, std::string title = "default slider");

	void init_title(SDL_Renderer* renderer, TTF_Font * font, std::string title);

	void update(Mouse mouse);
	void draw(SDL_Renderer*);
	~slider();
};

