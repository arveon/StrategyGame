#pragma once
#ifndef MAP_MANAGER
#define MAP_MANAGER
#include <iostream>

#include <vector>
#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_utils.hpp>

#include "sdl_manager.h"
#include "Tile.h"
#include "TilesetManager.h"
#include "HelperFunctions.h"
#include "Painter.h"

#include "LivingEntity.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

#include "LeePathfinder.h"

//Class to manage loading/saving of a map
class map_manager
{
private:
	static bool initialised;
	///static tileset_manager tileset_man;
	static int tileswide, tileshigh;
	static int  t_width, t_height;
	static tile_object*** map;
	static constants::pathfinding_tile*** tile_cost_map;
	static std::vector<living_entity*> map_entities;
	static std::vector<player*> players;
	static std::vector<item_object*> items;
	static void load_from_file();
	static bool map_currently_loaded;
public:
	///map initialisation functions
	static void load_required_tex_tiles();
	static void load_required_tex_players();
	static void load_required_tex_items();
	static void link_textures_to_tiles();
	static void link_textures_to_players();
	static void link_textures_to_items();
	static void load_map(int level);
	static bool link_tiles();
	static void init_pathfinding();
	static void init_pathfinding_for_current_map_state(int cur_player);

	static tile_object*** get_map() { return map; }
	static SDL_Point get_map_dimensions_t() { return {tileswide, tileshigh}; }
	static SDL_Point get_map_dimensions_px() { return { (int)((float)tileswide * t_width * constants::tile_scaling), (int)((float)(tileshigh * t_height) * constants::tile_scaling) }; }
	static int get_tile_size() { return t_width; }
	static int get_max_player_id() { return players.size() - 1; }

	static constants::tile_type get_tile_type_at(int x, int y);
	static player* get_player(int id) { return players.at(id); }

	static void world_tile_ids_at_mouse(int* to_save_x, int* to_save_y, int mouse_x, int mouse_y, SDL_Point cam_coords);
	static void world_tile_ids_at_coords(int* to_save_x, int* to_save_y, int x, int y);

	static std::vector<SDL_Point> get_path_from_to(int from_x, int from_y, int to_x, int to_y);

	static void initialise() { initialised = true; }
	static void unload_map();

	static void add_vector_to_painter(painter* drawing_manager, constants::base_object_type type);

	map_manager();
	~map_manager();
};

struct map_tile
{
public:
	int x, y;
	std::vector<map_tile*> neighbours;
};
#endif
