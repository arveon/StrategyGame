#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Constants.h"
#include "SplashScreen.h"

namespace sdlframework
{
	class game
	{
	private:
		struct RGB 
		{ 
			int R; 
			int G; 
			int B; 
			RGB(int r, int g, int b){ R = r; G = g; B = b; }
			RGB(){ R = 0; G = 0; B = 0; }
		};

		RGB cur_color;
		RGB dest_color;

		splash_screen splash;

		constants::game_state game_state;


		bool left_click;
		bool quit_game;
		bool pending_color_change;


	public:
		void init();
		void input();
		bool update(Uint32 deltaTime);
		void draw(SDL_Renderer*);

		void change_color();

		game();
		~game();
	};
}

