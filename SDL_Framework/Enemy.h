#pragma once
#include "LivingEntity.h"

///An enemy type of a living entity. Can be attacked by a player. Serves as an enemy player/monster
class enemy : public living_entity
{
public:
	enemy(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id, constants::entity_type);
	~enemy();
};

