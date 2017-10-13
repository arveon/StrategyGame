#include "Enemy.h"

enemy::enemy(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id, constants::entity_type ent_type) : living_entity(coords, width, height, texture, is_active, ent_type, texture_id)
{
}


enemy::~enemy()
{
}
