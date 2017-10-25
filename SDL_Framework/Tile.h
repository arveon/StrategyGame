#pragma once
#include <SDL.h>

#include "DrawableObject.h"
#include "Constants.h"

//A type of drawable object that represents a map tile (mostly terrain)
class tile_object : drawable_object
{
	friend class map_manager;
	friend class LeePathfinder;
private:
	std::vector<tile_object*> neighbours;
	int travel_cost = -1;
	int temp_pathfinder_value = -1;

	bool animated;
	int layer;
	///SDL_Texture* texture;
	SDL_Point world_coords;
	
	constants::tile_type tile_type;
public:
	tile_object(SDL_Point world_coords, int width, int height, bool active, SDL_Texture* texture, int layer, constants::tile_type type, int tile_texture_id);
	~tile_object();
	void add_neighbour(tile_object* neighbour) { neighbours.push_back(neighbour); };
	void set_travel_cost(int cost) { travel_cost = cost; }
	int get_travel_cost() { return travel_cost; }
};

