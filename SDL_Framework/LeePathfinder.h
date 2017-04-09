#pragma once
#include <vector>
#include "SimplePoint.h"
#include "Map.h"

class LeePathfinder
{
private:
	Map map;

	SimplePoint* start;
	SimplePoint end;
	bool path_found;
	std::vector<SimplePoint*> path;

	std::vector<SimplePoint*> mark_tile_neighbours(SimplePoint* tile, int num);
	//void mark_field(SimplePoint* start);

public:
	LeePathfinder(Map map);
	~LeePathfinder();

	void mark_field(SimplePoint* start);
	void calculate_path(SimplePoint* end);
	std::vector<SimplePoint*> get_path() { return path; }
	void display_field();
};

