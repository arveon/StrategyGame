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


	//menu buttons
	const int START_X = 550;
	const int START_Y = 100;

	const int LOAD_X = 550;
	const int LOAD_Y = 200;

	const int OPTIONS_X = 550;
	const int OPTIONS_Y = 300;

	const int EXIT_X = 550;
	const int EXIT_Y = 400;

	const int BUTTON_WIDTH = 150;
	const int BUTTON_HEIGHT = 50;

	const int CONFIRM_EXIT_DIALOG_WIDTH = 400;
	const int CONFIRM_EXIT_DIALOG_HEIGHT = 100;

	const std::string font_inkedout = "assets/fonts/Inked_Out.ttf";
};


#endif

