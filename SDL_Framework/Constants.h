#pragma once
#ifndef CONST_T
#define CONST_T
#include <SDL.h>
#include <string>

namespace constants
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;	
	const char WINDOW_CAPTION[] = "MyGame";

	const int NUM_SOUND_CHANNELS = 5;

	const bool SHOW_CURSOR = true;
	const float scaling_vertical = 1;
	const float scaling_horizontal = 1;
	
	
	enum game_state
	{
		splash,
		main_menu,
		pause_menu,
		game_flow
	};




};


#endif

