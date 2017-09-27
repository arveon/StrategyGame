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
	//TODO: move all following code into generic level parent and replace it with level::update(mouse);
	mouse->is_drawn = false;
	switch (loading_state)
	{
	case loading_map:
		map_manager::load_map(1);
		load_percent = 0.2;
		loading_state = loading_textures;
		break;
	case loading_textures:
		map_manager::load_required_tex();
		load_percent = 0.3;
		loading_state = attaching_textures;
		break;
	case attaching_textures:
		map_manager::link_textures_to_tiles();
		load_percent = 0.4;
		loading_state = linking_tiles;
		break;
	case linking_tiles:
		//map_manager::link_tiles(); - not implemented yet
		SDL_Delay(1000);
		load_percent = 0.6;
		loading_state = load_states::loading_tileset;
		break;
	case loading_tileset:
		SDL_Delay(1000);
		load_percent = 0.8;
		loading_state = load_states::done;
		break;
	case done:
		SDL_Delay(1000);
		load_percent = 1;
		is_loaded = true;
		mouse->is_drawn = true;

		tile_object*** map = map_manager::get_map();
		SDL_Point dimensions = map_manager::get_map_dimensions_t();
		for (int i = 0; i < dimensions.y; i++)
		{
			for (int j = 0; j < dimensions.x; j++)
			{
				drawing_manager->add_object_to_queue((drawable_object*)map[i][j]);
			}
		}
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
