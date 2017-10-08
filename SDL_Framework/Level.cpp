#include "Level.h"



level::level()
{
	loading_state = load_states::loading_map;
	load_percent = 0;
	is_loaded = false;
	// this->drawing_manager = drawing_manager;
}

void level::update_load(Mouse* mouse)
{
	mouse->is_drawn = false;
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
		//map_manager::link_tiles(); - not implemented yet
		//SDL_Delay(1000);
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
		mouse->is_drawn = true;
		map_manager::add_vector_to_painter(drawing_manager, constants::base_object_type::terrain);
		map_manager::add_vector_to_painter(drawing_manager, constants::base_object_type::character);

		/*tile_object*** map = map_manager::get_map();
		SDL_Point dimensions = map_manager::get_map_dimensions_t();
		for (int i = 0; i < dimensions.y; i++)
		{
			for (int j = 0; j < dimensions.x; j++)
			{
				drawing_manager->add_object_to_queue((drawable_object*)map[i][j]);
			}
		}*/


		break;
	}
}

void level::init(painter* ptr)
{
	drawing_manager = ptr;
}


level::~level()
{
}
