#include "LivingEntity.h"

living_entity::living_entity(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, constants::entity_type entity_type, int texture_id) : drawable_object(coords, width, height, is_active, texture, constants::base_object_type::character, texture_id)
{
	
}


living_entity::~living_entity()
{
}
