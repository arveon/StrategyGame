#pragma once
#include <SDL.h>

#include "DrawableObject.h"
#include "Constants.h"

class living_entity : drawable_object
{
public:
	living_entity(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active);
	~living_entity();
};

