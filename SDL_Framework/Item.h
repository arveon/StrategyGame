#pragma once
#include "DrawableObject.h"

///Is a generic item object that can be picked up by a player
class item_object : public drawable_object
{
public:
	item_object();
	~item_object();
};

