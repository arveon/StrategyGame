#include "Item.h"

//default constructor that creates an item at 0;0 coordinates with width=height=1 and 0th texture id
item_object::item_object() : drawable_object({0,0},1,1,false,nullptr,constants::base_object_type::item)
{
}

item_object::item_object(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id, constants::item_type type) : drawable_object(coords, width, height, true, texture, constants::base_object_type::item, texture_id)
{

}


item_object::~item_object()
{
}
