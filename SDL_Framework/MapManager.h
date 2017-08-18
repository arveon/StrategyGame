#pragma once
#include <iostream>

#include <vector>
#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_utils.hpp>

#include "sdl_manager.h"
#include "Tile.h"

class map_manager
{
private:
	static int w, h;
	static int  t_w, t_h;
	static tile_object*** map;

public:
	static void load_map(int level);
	static tile_object*** get_map() { return map; }

	void unload_map();
	map_manager();
	~map_manager();
};

struct map_tile
{
public:
	int x, y;
	std::vector<map_tile*> neighbours;
};

