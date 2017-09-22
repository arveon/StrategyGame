#include "Player.h"

player::player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active) : living_entity(coords, width, height, texture, is_active)
{


}


player::~player()
{
}
