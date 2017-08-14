#pragma once
#include <SDL.h>
class game_object
{
protected:
	SDL_Point world_coords;
	int width, height;

	bool active;
public:
	bool is_active() { return active; }
	void set_active(bool new_active) { active = new_active; }
	
	game_object(SDL_Point world_coords, int width, int height, bool active);
	~game_object();
};

