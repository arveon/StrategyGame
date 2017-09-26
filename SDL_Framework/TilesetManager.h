#pragma once
#include "sdl_manager.h"
#include <vector>

class tileset_manager
{
private:
	static SDL_Texture* tilesheet;
	static bool initialised;
	static std::vector<SDL_Texture*> tiles;
public:
	static void load_tiles(std::vector<int> tile_nums, constants::tilesets set, int tilewidth, int tileheight);//will load the tiles specified from the specified tileset
	static SDL_Texture* get_texture_by_id(constants::tilesets, int id);

	static void reset(); //will unload all of the tiles

	static void set_initialised() { initialised = true; }
	tileset_manager();
	~tileset_manager();
};

