#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Constants.h"


class drawable_object : game_object
{
	friend class painter;
protected:
	SDL_Texture* texture;
public:
	drawable_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, constants::base_object_type type);
	~drawable_object();
};

