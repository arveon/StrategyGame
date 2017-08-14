#pragma once
#include "sdl_manager.h"
#include <vector>

class tileset_manager
{
private:
	static std::vector<SDL_Texture*> tiles;
	

public:
	static void load_tiles(std::vector<int> tile_nums, constants::tilesets set);//will load the tiles specified from the specified tileset
	static void reset(); //will unload all of the tiles
	tileset_manager();
	~tileset_manager();
};

