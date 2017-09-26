#pragma once
#include <iostream>

#include <vector>
#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_utils.hpp>

#include "sdl_manager.h"
#include "Tile.h"
#include "TilesetManager.h"
#include "HelperFunctions.h"

class map_manager
{
private:
	static bool initialised;
	//static tileset_manager tileset_man;
	static int tileswide, tileshigh;
	static int  t_width, t_height;
	static tile_object*** map;

	static void load_from_file();
	static void list_tex_to_load();
	static void link_textures_to_tiles();
public:
	static void load_map(int level);
	static tile_object*** get_map() { return map; }
	static SDL_Point get_map_dimensions_t() { return {tileswide, tileshigh}; }
	static void initialise() { initialised = true; }
	void unload_map();
	map_manager();
	~map_manager();
};

struct map_tile
{
public:
	int x, y;
	std::vector<map_tile*> neighbours;
};

