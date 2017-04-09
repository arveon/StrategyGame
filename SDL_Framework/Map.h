#pragma once
#ifndef MAP_T
#define MAP_T
#include <iostream>
#include <vector>
#include "SimplePoint.h"

class Map
{
public:
	int width;
	int height;
	SimplePoint** field;
	//std::vector<SimplePoint*> field_v;

	Map() { field = nullptr; }
	Map(int width, int height);
	void populate_map_default();
	void link_tiles();
	void display_map();
	SimplePoint* get_tile(int x, int y) { return &field[y][x]; }

};
#endif