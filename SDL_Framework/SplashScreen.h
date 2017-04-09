#pragma once
#include <SDL.h>
#include <iostream>

#include "sdl_manager.h"

class splash_screen
{
private:
	enum state
	{
		Waiting,
		FadeIn,
		Static,
		FadeOut,
		Blank
	};

	state state;

	int elapsed_time;
	int total_screen_time = 5000;
	int animation_time = 1000;
	int wait_time = 1000;
	
	Uint8 transparency;
	SDL_Rect draw_rect;

public:
	SDL_Texture* image;
	void update(int delta_time);
	void draw(SDL_Renderer* renderer);
	bool is_splash_elapsed() { return state == state::Blank; }
	splash_screen(SDL_Renderer* renderer);
	splash_screen();
	~splash_screen();
};

