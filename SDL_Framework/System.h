#pragma once
#include "Game.h"
#include "Time.h"
#include "sdl_manager.h"
#include "FileHandler.h"
#include "ListItem.h"

#include <SDL.h>
#include <iostream>
#include <vector>

namespace sdlframework
{
	///Main class in the game that manages the time and contains the game loop
	class system
	{
	private:
		time time;
		game game;

		void init_constants();
	public:
		void init_system();
		void game_loop();
		void cleanup();

		system();
		~system();
	};
}

