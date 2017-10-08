#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Constants.h"


class drawable_object : public game_object
{
	friend class painter;
	friend class level_manager;
	friend class map_manager;
protected:
	int texture_id;
	SDL_Texture* texture;

	void change_texture(SDL_Texture* new_texture) { SDL_DestroyTexture(texture); texture = new_texture; }
public:
	drawable_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, constants::base_object_type type, int texture_id=0);
	~drawable_object();
};

