#include "LeePathfinder.h"



LeePathfinder::LeePathfinder(Map map)
{
	this->map = map;
	path_found = false;
	start = nullptr;
}

std::vector<SimplePoint*> LeePathfinder::mark_tile_neighbours(SimplePoint * tile, int num)
{
	std::vector<SimplePoint*> temp;
	//mark the neighbours
	for (int i = 0; i < tile->neighbours.size(); i++)
	{
		if (tile->neighbours.at(i)->val == 0)
		{
			tile->neighbours.at(i)->val = num;
			temp.push_back(tile->neighbours.at(i));
		}
		else if (tile->neighbours.at(i)->val == -11)
		{
			std::vector<SimplePoint*> empty;
			path_found = true;
			return empty;
		}
	}

	return temp;
}

void LeePathfinder::mark_field(SimplePoint* start)
{
	//if start position not inside wall, set start position
	if (map.get_tile(start->x, start->y)->val != -1)
		this->start = start;
	else
		this->start = nullptr;

	int num = 1;
	static std::vector<SimplePoint*> cur_number = mark_tile_neighbours(start, num);
	//std::cout << std::endl << cur_number.size() << std::endl;
	while (!path_found)
	{
		//cout << cur_number.size() << endl;
		num++;
		std::vector<SimplePoint*> iteration_points;
		for (int i = 0; i < cur_number.size(); i++)
		{
			std::vector<SimplePoint*> t1 = mark_tile_neighbours(cur_number.at(i), num);
			for (int j = 0; j < t1.size(); j++)
				iteration_points.push_back(t1.at(j));
		}

		cur_number = iteration_points;
		//if there is no more tiles to be marked, stop looping
		if (iteration_points.size() == 0)
		{
			if(this->start != nullptr)
				map.get_tile(start->x, start->y)->val = -10;
			return;
		}
	}
	if (this->start != nullptr)
		map.get_tile(start->x, start->y)->val = -10;
}

//backtrack
void LeePathfinder::calculate_path(SimplePoint * end)
{
	SimplePoint* cur_point = end;
	//path.push_back(endpoint);
	bool start_reached = false;
	while (!start_reached)
	{
		SimplePoint* min_point = cur_point->neighbours.at(0);
		int counter = 1;
		while (min_point->val == -1)
		{
			min_point = cur_point->neighbours.at(counter);
			counter++;
		}

		for (int i = 0; i < cur_point->neighbours.size(); i++)
		{
			if (min_point->val > cur_point->neighbours.at(i)->val &&
				cur_point->neighbours.at(i)->val != 0 &&
				cur_point->neighbours.at(i)->val != -11 &&
				cur_point->neighbours.at(i)->val != -1)
				min_point = cur_point->neighbours.at(i);
		}

		SimplePoint* temp = new SimplePoint{ min_point->x, min_point->y, 3 };

		if (min_point->val == -10)
			start_reached = true;
		else
			path.push_back(temp);

		cur_point = min_point;
	}
}

void LeePathfinder::display_field()
{
	map.display_map();
}

LeePathfinder::~LeePathfinder()
{
}


