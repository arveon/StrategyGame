#include "TilesetManager.h"

bool tileset_manager::initialised = false;
SDL_Texture* tileset_manager::tilesheet = nullptr;
std::vector<SDL_Texture*> tileset_manager::tiles;
void tileset_manager::load_tiles(std::vector<int> tile_nums, constants::tilesets set, int tilewidth, int tileheight)
{
	tiles.resize(2);
	if (initialised)
	{
		switch (set)
		{
		case constants::tilesets::map:
			tilesheet = sdlframework::sdl_manager::load_png_texture(constants::TILESET_TERRAIN_PATH);
			break;
		}

		for (std::vector<int>::iterator it = tile_nums.begin(); it != tile_nums.end(); it++)
		{
			int across, down, id = *it;
			down = std::floor((float)id / (float)constants::tileset_width);
			across = id - (down * 4);
			SDL_Rect rect = { across*tilewidth, down * tileheight, tilewidth, tileheight };
			if (tiles.size() <= id) tiles.resize(id+1);
			tiles.at(id) = sdlframework::sdl_manager::get_texture_from_tilesheet(tilesheet, rect);
		}
		
	}
}

SDL_Texture* tileset_manager::get_texture_by_id(constants::tilesets tileset, int id)
{
	SDL_Texture* result = nullptr;
	if (initialised)
	{
		switch (tileset)
		{
		case constants::tilesets::map:
			result = tiles.at(id);
			break;
		}	
	}
	return result;
}

void tileset_manager::reset()
{
}

tileset_manager::tileset_manager()
{
}


tileset_manager::~tileset_manager()
{
}
