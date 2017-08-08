#pragma once
#ifndef CONST_T
#define CONST_T
#include <SDL.h>
#include <string>

///namespace contains all of the game and system constants
namespace constants
{
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;
	const char WINDOW_CAPTION[] = "MyGame";

	const int NUM_SOUND_CHANNELS = 5;

	const bool SHOW_CURSOR = true;
	const float scaling_vertical = (float)WINDOW_HEIGHT / 480;
	const float scaling_horizontal = (float)WINDOW_WIDTH / 640;

	enum game_state
	{
		splash,
		main_menu,
		pause_menu,
		game_flow,
		confirming_exit,
		exit_confirmed
	};

	//menu buttons
	const int START_X = 380;
	const int START_Y = 100;

	const int LOAD_X = 380;
	const int LOAD_Y = 200;

	const int OPTIONS_X = 380;
	const int OPTIONS_Y = 300;

	const int EXIT_X = 380;
	const int EXIT_Y = 400;

	const int BUTTON_WIDTH = 150;
	const int BUTTON_HEIGHT = 50;

	const int CONFIRM_EXIT_DIALOG_WIDTH = 400;
	const int CONFIRM_EXIT_DIALOG_HEIGHT = 100;

	const int MAIN_MENU_BUTTON_FONT_SIZE = 16;

	const std::string MOUSE_PATH = "assets/graphics/mouse.png";

	const std::string FONTS_PATH = "assets/fonts/";
	const std::string font_inkedout = "Inked_Out.ttf";
	const std::string font_optimus = "Optimus_Princeps_Semi_Bold.ttf";

	const SDL_Color SECONDARY_MENU_SLIDER_COLOR = SDL_Color{ 255, 255, 255 };

	const std::string SAVES_PATH = "saves";


	//OPTIONS MENU POSITIONING and other
	const SDL_Point VOLUME_SLIDER_POS = {10,100};
	const SDL_Point MUSIC_SLIDER_POS = { 10,160 };
	const SDL_Point SOUNDS_SLIDER_POS = { 10,220 };
	const SDL_Point FULLSCREEN_CHECKBOX_POS = {400, 80};
	const SDL_Point RESOLUTIONS_LIST_POS = {400, 140};
	const int RESOLUTION_LIST_WIDTH = 170;
	const int RESOLUTION_LIST_HEIGHT = 100;
	const int SLIDER_WIDTH = 300;
	const int SLIDER_HEIGHT = 10;


	//general UI constants
	const int TEXT_SLIDER_GAP = 35;
};


#endif

