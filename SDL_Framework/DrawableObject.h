#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Constants.h"

///Class represents a generic drawable game object
class drawable_object : public game_object
{
	friend class painter;
	friend class level_manager;
	friend class map_manager;
protected:
	int texture_id;//id of a texture inside the appropriate tilesheet
	SDL_Texture* texture;

	void change_texture(SDL_Texture* new_texture) { SDL_DestroyTexture(texture); texture = new_texture; }
public:
	drawable_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, constants::base_object_type type, int texture_id=0);
	~drawable_object();
};

