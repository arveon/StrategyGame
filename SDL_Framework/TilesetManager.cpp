#include "TilesetManager.h"

bool tileset_manager::initialised = false;
SDL_Texture* tileset_manager::tilesheet = nullptr;
std::vector<SDL_Texture*> tileset_manager::tiles;
tileset_manager::tilesheet_state tileset_manager::state;
std::vector<SDL_Texture*> tileset_manager::entities;
void tileset_manager::load_tiles(std::vector<int> tile_nums, constants::tilesets set, int tilewidth, int tileheight)
{
	tiles.resize(2);
	if (initialised)
	{
		std::vector<SDL_Texture*>* vector_used = nullptr;
		switch (set)
		{
		case constants::tilesets::map:
			if (state != tilesheet_state::terrain)
			{
				if (state != tilesheet_state::empty)
					SDL_DestroyTexture(tilesheet);
				tilesheet = sdlframework::sdl_manager::load_png_texture(constants::TILESET_TERRAIN_PATH);
				state = tilesheet_state::terrain;
			}
			vector_used = &tiles;
			break;
		case constants::tilesets::characters:
			if (state != tilesheet_state::characters)
			{
				if (state != tilesheet_state::empty)
					SDL_DestroyTexture(tilesheet);
				tilesheet = sdlframework::sdl_manager::load_png_texture(constants::TILESET_CHARACTERS_PATH);
				state = tilesheet_state::characters;
			}
			vector_used = &entities;
			break;
		}


		for (std::vector<int>::iterator it = tile_nums.begin(); it != tile_nums.end(); it++)
		{
			int across, down, id = *it;
			down =(int)std::floor((float)id / (float)constants::tileset_width);
			across = id - (down * constants::tileset_width);
			SDL_Rect rect = { across*tilewidth, down * tileheight, tilewidth, tileheight };
			if ((int)vector_used->size() <= id) vector_used->resize(id+1);
			vector_used->at(id) = sdlframework::sdl_manager::get_texture_from_tilesheet(tilesheet, rect);
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
		case constants::tilesets::characters:
			result = entities.at(id);
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
