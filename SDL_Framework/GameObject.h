#pragma once
#include <SDL.h>
#include "Constants.h"

class game_object
{
protected:
	SDL_Point world_coords;
	int width, height;

	bool active;

	constants::base_object_type type;
public:
	bool is_active() { return active; }
	void set_active(bool new_active) { active = new_active; }
	SDL_Point get_position() { return world_coords; }
	constants::base_object_type get_type() { return type; }
	
	game_object(SDL_Point world_coords, int width, int height, bool active, constants::base_object_type type = constants::base_object_type::other);
	~game_object();
};

