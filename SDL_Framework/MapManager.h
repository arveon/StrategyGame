#pragma once
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


class map_manager
{
private:
	static bool initialised;
	//static tileset_manager tileset_man;
	static int tileswide, tileshigh;
	static int  t_width, t_height;
	static tile_object*** map;
	static std::vector<living_entity*> map_entities;
	static std::vector<item_object*> items;
	static void load_from_file();
public:
	static void load_required_tex_tiles();
	static void load_required_tex_entities();
	static void link_textures_to_tiles();
	static void link_textures_to_entities();
	static void load_map(int level);
	static tile_object*** get_map() { return map; }
	static SDL_Point get_map_dimensions_t() { return {tileswide, tileshigh}; }
	static SDL_Point get_map_dimensions_px() { return { (int)((float)tileswide * t_width * constants::tile_scaling), (int)((float)(tileshigh * t_height) * constants::tile_scaling) }; }
	static int get_tile_size() { return t_width; };
	static constants::tile_type get_tile_type_at(int x, int y);
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

