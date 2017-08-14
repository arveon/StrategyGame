#pragma once
#include <SDL.h>
#include "GameObject.h"


class drawable_object : game_object
{
protected:
	SDL_Texture* texture;
	int layer;
public:
	drawable_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, int layer = 1);
	~drawable_object();
};

