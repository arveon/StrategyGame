#pragma once
#include <SDL.h>
#include <iostream>

#include "sdl_manager.h"

//class that represents a splash screen shown in the beginning of the game
class splash_screen
{
private:
	//different states of the splash screen
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
	int animation_time = 1000;//time of animation
	int wait_time = 1000;//time when nothing happens before splash screen appears
	
	float transparency;//transparency of the splash screen
	SDL_Rect draw_rect;//destination rectangle of the splash sccreen

public:
	SDL_Texture* image;
	void update(int delta_time);
	void draw(SDL_Renderer* renderer);
	bool is_splash_elapsed() { return state == state::Blank; }
	splash_screen(SDL_Renderer* renderer);
	splash_screen();
	~splash_screen();
};

