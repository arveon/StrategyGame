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
		loading,
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
	const std::string font_libertine = "LinLibertine.ttf";

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
	const SDL_Point LOAD_BAR_POS = { 20, 400 };
	const SDL_Point LOAD_BAR_SIZE = {600, 50};
	const SDL_Point LOAD_TEXT_POS = {20, 370};
	const SDL_Point GPI_TILE_TYPE_POS_MARGIN = {20,-40};

	//file templates
	const std::string LAUNCH_MIN_TEMPLATE = "appname StratGame\nresolution 640 480\nfullscreen 1";
	const std::string SETTINGS_MIN_TEMPLATE = "master_volume 100\nmusic_volume 100\nsounds_volume 100\nfullscreen 0\nresolution 0";

	struct pathfinding_tile
	{
		SDL_Point position;
		int cost;
		int pathfinding_num;
		std::vector<pathfinding_tile*> neighbours;
		bool origin;
		bool destination;
		bool blocked;
	};

	//map constants
	const int misc_num_items = 2;
	const int tileset_width = 8;
	const int tileset_entity_offset = 85;
	const float tile_scaling = 1;
	const enum tilesets
	{
		map,
		characters,
		props,
		items,
		misc
	};
	const std::string TILESET_TERRAIN_PATH = "assets/tilesets/terrain.png";
	const std::string TILESET_CHARACTERS_PATH = "assets/tilesets/characters.png";
	const std::string TILESET_MISC_PATH = "assets/tilesets/misc.png";

	const enum tile_type
	{
		empty,
		earth,
		grass,
		mud,
		road,
		stone,
		water,
		pl,
		game_obj,
		entity
	};

	const enum entity_type
	{
		player = 0,
		enemy_ai_1 = 1,
		enemy_ai_2 = 2,
		enemy_ai_3 = 3,
		enemy_ai_4 = 4,
		enemy_ai_5 = 5,
		friendly_ai = 7
	};

	const enum item_type
	{
		tree_trunk,
		tree,

	};

	const enum misc_tile
	{
		path_tile = 0,
		end_path_tile = 1
	};

	//game constants
	const enum base_object_type
	{
		terrain,
		character,
		item,
		path,
		ui,
		other
	};


	class setup
	{
	public:
		static int tile_height, tile_width;
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

