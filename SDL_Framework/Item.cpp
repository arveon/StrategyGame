#include "Item.h"

//default constructor that creates an item at 0;0 coordinates with width=height=1 and 0th texture id
item_object::item_object() : drawable_object({0,0},1,1,false,nullptr,constants::base_object_type::item)
{
}


item_object::~item_object()
{
}
