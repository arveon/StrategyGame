#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Constants.h"


class drawable_object : game_object
{
	friend class painter;
	friend class level_manager;
protected:
	SDL_Texture* texture;

	void change_texture(SDL_Texture* new_texture) { SDL_DestroyTexture(texture); texture = new_texture; }
public:
	drawable_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, constants::base_object_type type);
	~drawable_object();
};

