#pragma once
#include <SDL.h>
#include "DrawableObject.h"
#include "Constants.h"

class tile_object : drawable_object
{
private:
	bool animated;
	int layer;
	SDL_Texture* texture;
	SDL_Point world_coords;
public:
	tile_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, int layer, constants::tile_type type);
	~tile_object();
};

