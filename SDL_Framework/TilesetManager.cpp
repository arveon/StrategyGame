#include "TilesetManager.h"

//initialise all of the static fields
bool tileset_manager::initialised = false;
SDL_Texture* tileset_manager::tilesheet = nullptr;
std::vector<SDL_Texture*> tileset_manager::tiles;
tileset_manager::tilesheet_state tileset_manager::state;
std::vector<SDL_Texture*> tileset_manager::entities;

///function loads the textures with ids provided in tile_nums from an appropriate set
void tileset_manager::load_tiles(std::vector<int> tile_nums, constants::tilesets set, int tilewidth, int tileheight)
{
	tiles.resize(2);//just to get rid of some errors connected to vector size
	if (initialised)//need this if because static functions are called at program start as well
	{
		//mechanism that allows to add textures to an appropriate vector and from appropriate tilesheet without reloading it for every tile
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

		//loop through vector and load all of the required textures
		for (std::vector<int>::iterator it = tile_nums.begin(); it != tile_nums.end(); it++)
		{
			int across, down, id = *it;
			//calculate the coordinates of the required texture within the tilesheet
			down =(int)std::floor((float)id / (float)constants::tileset_width);
			across = id - (down * constants::tileset_width);
			SDL_Rect rect = { across*tilewidth, down * tileheight, tilewidth, tileheight };
			//load the texture and put it at its id index in vector so its easier to use them later and get them from the vector
			if ((int)vector_used->size() <= id) vector_used->resize(id+1);//if vector too small for the id, resize the vector
			vector_used->at(id) = sdlframework::sdl_manager::get_texture_from_tilesheet(tilesheet, rect);
		}
		
	}
}

///Functions returns the texture with the given id from a given tileset
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
