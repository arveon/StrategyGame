#pragma once
#include <SDL.h>

#include "DrawableObject.h"
#include "Constants.h"

class tile_object : drawable_object
{
	friend class map_manager;
private:
	bool animated;
	int layer;
	//SDL_Texture* texture;
	SDL_Point world_coords;
	
	constants::tile_type tile_type;
public:
	tile_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, int layer, constants::tile_type type, int tile_texture_id);
	~tile_object();
};

