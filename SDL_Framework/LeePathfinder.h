#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Constants.h"
#include "Tile.h"

class LeePathfinder
{
private:
	static constants::pathfinding_tile*** map;
	static int width, height;
	static SDL_Point origin;
	static SDL_Point destination;
	static bool path_found;
	static std::vector<SDL_Point> path;

	static std::vector<SDL_Point> cur_players;

	static std::vector<constants::pathfinding_tile*> mark_tile_neighbours(constants::pathfinding_tile* tile, int num);
	static bool calculate_path(constants::pathfinding_tile* end);
public:
	LeePathfinder();
	~LeePathfinder();
	static void set_map(constants::pathfinding_tile*** map, int w, int h) { LeePathfinder::map = map; width = w; height = h; }
	static void set_origin(int x, int y);
	static void set_destination(int x, int y);
	static void set_players(std::vector<SDL_Point> player_positions);
	static void set_objects(std::vector<SDL_Point> object_positions);

	static SDL_Point get_origin() { return origin; }

	static void mark_field(constants::pathfinding_tile* start = map[origin.y][origin.x]);
	static bool find_path(SDL_Point end);

	static std::vector<SDL_Point> get_path() { return path; }
	static void display_field();
};

