#pragma once
#include "LivingEntity.h"
///A type of living entity that is the main player
class player : public living_entity
{
public:
	

	player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id);
	~player();
};

