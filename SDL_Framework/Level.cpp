#include "Level.h"


//level initialisation
level::level()
{
	loading_state = load_states::loading_map;
	load_percent = 0;
	is_loaded = false;
	// this->drawing_manager = drawing_manager;
}

///Function called from main update of a specific level to update the loading screen of the level
void level::update_load(Mouse* mouse)
{
	//mouse shouldn't be drawn while level is loading
	mouse->is_drawn = false;
	//depending on the state do an appropriate action
	switch (loading_state)
	{
	case loading_map:
		map_manager::load_map(1);
		load_percent = 0.1f;
		loading_state = loading_map_textures;
		break;
	case loading_map_textures:
		map_manager::load_required_tex_tiles();
		load_percent = 0.2f;
		loading_state = attaching_map_textures;
		break;
	case attaching_map_textures:
		map_manager::link_textures_to_tiles();
		load_percent = 0.3f;
		loading_state = loading_character_textures;
		break;
	case loading_character_textures:
		map_manager::load_required_tex_entities();
		load_percent = 0.4f;
		loading_state = attaching_character_textures;
		break;
	case attaching_character_textures:
		map_manager::link_textures_to_entities();
		load_percent = 0.5f;
		loading_state = cleaning_up_tilesheet;
		break;
	case cleaning_up_tilesheet:
		tileset_manager::unload_tilesheet();
		load_percent = 0.6f;
		loading_state = linking_tiles;
		break;
	case linking_tiles:
		if (!map_manager::link_tiles())
			std::cout << "MAP NOT LOADED YET" << std::endl;
		load_percent = 0.7f;
		loading_state = load_states::loading_tileset;
		break;
	case loading_tileset:
		//SDL_Delay(1000);
		load_percent = 0.8f;
		loading_state = load_states::done;
		break;
	case done:
		//SDL_Delay(1000);
		load_percent = 1;
		is_loaded = true;
		//draw mouse when done loading
		//also add all of the elements to painter
		mouse->is_drawn = true;
		map_manager::add_vector_to_painter(drawing_manager, constants::base_object_type::terrain);
		map_manager::add_vector_to_painter(drawing_manager, constants::base_object_type::character);
		break;
	}
}

///In case need a painter reference inside of level
void level::init(painter* ptr)
{
	drawing_manager = ptr;
}


level::~level()
{
}
