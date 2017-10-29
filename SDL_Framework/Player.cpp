#include "Player.h"

player::player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id) : living_entity(coords, width, height, texture, is_active, constants::entity_type::player, texture_id)
{
}


player::~player()
{
}

void player::move()
{
	moving = true;
	next_tile = path.at(path.size()-1);
	next_tile.x *= constants::setup::tile_width;
	next_tile.y *= constants::setup::tile_height;

	prev_tile = world_coords;
	//this->world_coords = { path.at(0).x * constants::setup::tile_width,  path.at(0).y * constants::setup::tile_height};
}

void player::update(Mouse* mouse, int delta_time)
{
	if (moving)
	{
		mouse->is_drawn = false;

		elapsed_tile_move_time += delta_time;
		if (elapsed_tile_move_time > total_tile_move_time)
		{
			path_tile_done = true;
			prev_tile = next_tile;
			world_coords = next_tile;
			path.pop_back();
			if (path.size() > 0)
			{
				next_tile = path.at(path.size() - 1);
				next_tile.x *= constants::setup::tile_width;
				next_tile.y *= constants::setup::tile_height;
			}
			else
			{
				finished_movement = true;
				moving = false;
			}

			elapsed_tile_move_time = 0;
		}
		else
		{
			SDL_Point deltapos = { ((float)next_tile.x - (float)prev_tile.x) * ((float)elapsed_tile_move_time/(float)total_tile_move_time), ((float)next_tile.y - (float)prev_tile.y) * ((float)elapsed_tile_move_time / (float)total_tile_move_time) };
			world_coords = {prev_tile.x + deltapos.x, prev_tile.y + deltapos.y};
		}


	}
	else
	{
		mouse->is_drawn = true;
	}
}

bool player::is_dest_same(SDL_Point new_dest)
{ 
	if (path.size() == 0)
		return false;
	return (path.at(0).x == new_dest.x && path.at(0).y == new_dest.y); 
}