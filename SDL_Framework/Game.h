#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Constants.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Mouse.h"

namespace sdlframework
{
	///Class represents the game that is being run by the game loop
	///Top-level of the actual game logic
	///Responsible for keeping track and managing the global game state
	class game
	{
	private:
		constants::game_state game_state;

		splash_screen splash;
		main_menu menu;
		confirm_dialog* exit_confirm = nullptr;
		constants::game_state state_before_exit = constants::game_state::splash;

		Mouse mouse;

		bool quit_game;
		bool pending_color_change;
	public:
		void init();
		void input();
		bool update(Uint32 deltaTime);
		void draw(SDL_Renderer*);

		game();
		~game();
	};
}

