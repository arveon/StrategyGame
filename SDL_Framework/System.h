#pragma once
#include "Game.h"
#include "Time.h"
#include "sdl_manager.h"

#include <SDL.h>
#include <iostream>

namespace sdlframework
{
	///Main class in the game that manages the time and contains the game loop
	class system
	{
	private:
		time time;
		game game;

	public:
		void init_system();
		void game_loop();
		void cleanup();

		system();
		~system();
	};
}

