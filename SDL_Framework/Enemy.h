#pragma once
#include "LivingEntity.h"

class enemy : public living_entity
{
public:
	enemy(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id, constants::entity_type);
	~enemy();
};

