#pragma once
#include "DrawableObject.h"

///Is a generic item object that can be picked up by a player
class item_object : public drawable_object
{
private:
	bool solid;
	std::string item_name;
	constants::item_type i_type;
public:
	item_object();
	item_object(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_collidable, int texture_id, constants::item_type type, std::string name);
	~item_object();

	std::string get_item_name() { return item_name; }
	constants::item_type get_item_type() { return i_type; }
};

