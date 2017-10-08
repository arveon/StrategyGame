#pragma once
#include <SDL.h>

#include "DrawableObject.h"
#include "Constants.h"

class living_entity : public drawable_object
{
protected:
	int health;

	constants::entity_type type;
public:
	living_entity(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, constants::entity_type, int texture_id);
	~living_entity();
};

