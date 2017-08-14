#include "Tile.h"



tile_object::tile_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, int layer, constants::tile_type type) : drawable_object(world_coords, width, height, active, texture, layer)
{
}


tile_object::~tile_object()
{
}
