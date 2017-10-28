#include "Player.h"

player::player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id) : living_entity(coords, width, height, texture, is_active, constants::entity_type::player, texture_id)
{


}


player::~player()
{
}

void player::move()
{
	this->world_coords = { path.at(0).x * constants::setup::tile_width,  path.at(0).y * constants::setup::tile_height};
}

bool player::is_dest_same(SDL_Point new_dest)
{ 
	if (path.size() == 0)
		return false;
	return (path.at(0).x == new_dest.x && path.at(0).y == new_dest.y); 
}