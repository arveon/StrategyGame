#pragma once
#include <SDL.h>

#include "Constants.h"
#include "sdl_manager.h"
///
///Class serves as a representation of mouse states. It contains x, y, button current and previous positions
///as well as methods to draw and update it
class Mouse
{
private:
	SDL_Texture* texture;
	SDL_Rect draw_rect;
public:
	bool is_drawn;

	int x, y;
	bool lmb_down;
	bool rmb_down;
	bool prev_lmb_down;
	bool prev_rmb_down;
	Mouse(){}
	~Mouse(){}

	void init()
	{
		is_drawn = true;
		texture = sdlframework::sdl_manager::load_png_texture(constants::MOUSE_PATH);
		draw_rect.x = 0;
		draw_rect.y = 0;
		draw_rect.w = 40;
		draw_rect.h = 40;
		//SDL_QueryTexture(texture, NULL, NULL, &draw_rect.w, &draw_rect.h);
	}

	void update()
	{
		draw_rect.x = x;
		draw_rect.y = y;
	}
	
	void draw(SDL_Renderer* renderer)
	{
		if (is_drawn)
			SDL_RenderCopy(renderer, texture, NULL, &draw_rect);
	}
};

