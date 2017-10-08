#include "Player.h"

player::player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id) : living_entity(coords, width, height, texture, is_active, constants::entity_type::player, texture_id)
{


}


player::~player()
{
}
