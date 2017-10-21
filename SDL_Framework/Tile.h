#pragma once
#include <SDL.h>

#include "DrawableObject.h"
#include "Constants.h"

//A type of drawable object that represents a map tile (mostly terrain)
class tile_object : drawable_object
{
	friend class map_manager;
private:
	std::vector<tile_object*> neighbours;

	bool animated;
	int layer;
	///SDL_Texture* texture;
	SDL_Point world_coords;
	
	constants::tile_type tile_type;
public:
	tile_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, int layer, constants::tile_type type, int tile_texture_id);
	~tile_object();
	void add_neighbour(tile_object* neighbour) { neighbours.push_back(neighbour); };
};

