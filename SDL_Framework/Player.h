#pragma once
#include "LivingEntity.h"

class player : living_entity
{
protected:
	int health;
public:
	player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active);
	~player();
};

