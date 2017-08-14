#include "DrawableObject.h"



drawable_object::drawable_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, int layer) : game_object(world_coords, width, height, active)
{
	this->texture = texture;
	this->layer = layer;
}


drawable_object::~drawable_object()
{
}
