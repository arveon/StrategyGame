#pragma once
#include "DrawableObject.h"

///Is a generic item object that can be picked up by a player
class item_object : public drawable_object
{
private:
	bool solid;
public:
	item_object();
	item_object(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_collidable, int texture_id, constants::item_type type);
	~item_object();
};

