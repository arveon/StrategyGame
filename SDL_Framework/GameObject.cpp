#include "GameObject.h"



game_object::game_object(SDL_Point world_coords, int width, int height, bool active, constants::base_object_type type)
{
	this->world_coords = world_coords;
	this->width = width;
	this->height = height;
	this->active = active;
}


game_object::~game_object()
{
}