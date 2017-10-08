#pragma once
#include "LivingEntity.h"

class player : public living_entity
{
public:
	player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id);
	~player();
};

