#pragma once
#include <SDL.h>

#include "Mouse.h"

class item_list
{
public:
	void draw(SDL_Renderer* renderer);
	void Update(Mouse mouse);

	item_list();
	~item_list();
};

