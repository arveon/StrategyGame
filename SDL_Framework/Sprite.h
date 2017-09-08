#pragma once
#include <SDL.h>

class sprite
{
public:
	SDL_Texture* texture;
	SDL_Rect draw_rect;

	~sprite() { SDL_DestroyTexture(texture); }
};