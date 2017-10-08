#include "DrawableObject.h"



drawable_object::drawable_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, constants::base_object_type type, int texture_id) : game_object(world_coords, width, height, active, type)
{
	this->texture = texture;
	this->texture_id = texture_id;
}


drawable_object::~drawable_object()
{
}
