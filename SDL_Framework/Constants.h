#ifndef CONST_T
#define CONST_T
#include <SDL.h>
#include <string>
#include <vector>
#include <sstream>

#include "ListItem.h"

///namespace contains all of the game and system constants
namespace constants
{

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
	const SDL_Point VOLUME_SLIDER_POS = { 10,100 };
	const SDL_Point MUSIC_SLIDER_POS = { 10,160 };
	const SDL_Point SOUNDS_SLIDER_POS = { 10,220 };
	const SDL_Point FULLSCREEN_CHECKBOX_POS = { 400, 80 };
	const SDL_Point RESOLUTIONS_LIST_POS = { 400, 140 };
	const int RESOLUTION_LIST_WIDTH = 170;
	const int RESOLUTION_LIST_HEIGHT = 100;
	const int SLIDER_WIDTH = 300;
	const int SLIDER_HEIGHT = 10;


	//general UI constants
	const int TEXT_SLIDER_GAP = 35;

	//file templates
	const std::string LAUNCH_MIN_TEMPLATE = "appname StratGame\nresolution 640 480\nfullscreen 1";
	const std::string SETTINGS_MIN_TEMPLATE = "master_volume 100\nmusic_volume 100\nsounds_volume 100\nfullscreen 0\nresolution 0";

	class setup
	{
	public:
		static int WINDOW_WIDTH;
		static int WINDOW_HEIGHT;
		static float scaling_vertical/* = (float)WINDOW_HEIGHT / 480*/;
		static float scaling_horizontal/* = (float)WINDOW_WIDTH / 640*/;
		static const int NUM_SOUND_CHANNELS = 5;
		static const bool SHOW_CURSOR = true;
		static bool FULLSCREEN;
		static std::string WINDOW_CAPTION;

		static void init_resolution_deps();
		static void init_settings(std::vector<list_item> settings);
	};
};
#endif

