#include "Level.h"


//level initialisation
level::level()
{
	current_player = 0;

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
		map_manager::load_required_tex_players();
		load_percent = 0.4f;
		loading_state = attaching_character_textures;
		break;
	case attaching_character_textures:
		map_manager::link_textures_to_players();
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
		loading_state = load_states::initialising_pathfinding;
		break;
	case initialising_pathfinding:
		map_manager::init_pathfinding();
		load_percent = 0.8f;
		loading_state = load_states::loading_misc;
		break;
	case loading_misc:
		tileset_manager::load_misc(map_manager::get_tile_size(), map_manager::get_tile_size());
		load_percent = 0.9f;
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

void level::mouse_clicked_at(int x, int y, constants::tile_type tile_clicked_at)
{
	//TODO: movement logic
	player* cur_player = map_manager::get_player(current_player);
	int p_x = 0, p_y = 0;
	map_manager::world_tile_ids_at_coords(&p_x, &p_y, cur_player->get_position().x, cur_player->get_position().y);
	map_manager::init_pathfinding_for_current_map_state(current_player);

	if (p_x == x && p_y == y)
		return;

	if (map_manager::get_player(current_player)->is_dest_same({ x, y }))
	{
		std::cout << "Player moved" << std::endl;
		map_manager::get_player(current_player)->move();
		drawing_manager->remove_old_path();
		//reset pathfinding for current player
		map_manager::init_pathfinding_for_current_map_state(current_player);
		return;
	}

	std::vector<SDL_Point> path = map_manager::get_path_from_to(p_x, p_y, x, y);
	map_manager::get_player(current_player)->set_path(path);
	std::cout << "Path from: " << p_x << ":" << p_y << " to " << x << ":" << y << " takes " << path.size() << " steps." << std::endl;
	
	///if tile found, remove old and add new
	if (path.size() > 0)
	{
		drawing_manager->remove_old_path();
		///add finish tile
		///create objects for path and add them to render queue
		for (int i = path.size() - 1; i >= 0; i--)
		{
			drawable_object* path_tile = nullptr;
			if(i != 0)
				path_tile = new drawable_object({ path.at(i).x * map_manager::get_tile_size(),  path.at(i).y * map_manager::get_tile_size() }, map_manager::get_tile_size(), map_manager::get_tile_size(), true, tileset_manager::get_texture_by_id(constants::tilesets::misc, constants::misc_tile::path_tile), constants::base_object_type::path, constants::misc_tile::path_tile);
			else if (i == 0)
				path_tile = new drawable_object({ x * map_manager::get_tile_size(),  y * map_manager::get_tile_size() }, map_manager::get_tile_size(), map_manager::get_tile_size(), true, tileset_manager::get_texture_by_id(constants::tilesets::misc, constants::misc_tile::end_path_tile), constants::base_object_type::path, constants::misc_tile::end_path_tile);
			drawing_manager->add_object_to_queue(path_tile);
		}
	}

}


level::~level()
{
}
