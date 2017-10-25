#include "LeePathfinder.h"

constants::pathfinding_tile*** LeePathfinder::map;
int LeePathfinder::width, LeePathfinder::height;
SDL_Point LeePathfinder::origin;
SDL_Point LeePathfinder::destination;
bool LeePathfinder::path_found;
std::vector<SDL_Point> LeePathfinder::path;

LeePathfinder::LeePathfinder()
{
	path_found = false;
	origin = {0,0};
}

//this function will loop through the given tile neighbours, mark them with the given number and return the vector containing neighbours of all of the tiles neighbours
std::vector<constants::pathfinding_tile*> LeePathfinder::mark_tile_neighbours(constants::pathfinding_tile* tile, int num)
{
	std::vector<constants::pathfinding_tile*> to_mark_next;
	///will mark all of the given tile's neighbours and if they are not marked, will mark them
	///also will add them to the list of tile whose neighbours will be marked in the next iteration of the mark_field main loop
	for (int i = 0; i < (int)tile->neighbours.size(); i++)
	{
		if (tile->neighbours.at(i)->pathfinding_num == 0)
		{
			tile->neighbours.at(i)->pathfinding_num = num;
			to_mark_next.push_back(tile->neighbours.at(i));
		}
		else if (tile->neighbours.at(i)->pathfinding_num == -11)
		{
			std::vector<constants::pathfinding_tile*> empty;
			path_found = true;
			return empty;
		}
	}

	return to_mark_next;
}

void LeePathfinder::mark_field(constants::pathfinding_tile* start)
{
	//if start position not inside wall, set origin position
	if (map[start->position.y][start->position.x]->pathfinding_num != -1)
		origin = start->position;
	else
		origin = {0,0};

	int num = 1;
	//cur_number vector is used to store all of the tiles that will be marked in the current iteration (a current generation of tiles
	static std::vector<constants::pathfinding_tile*> cur_generation = mark_tile_neighbours(start, num);
	
	//one iteration of the loop - one generation of tiles (e.g. all of the first neighbours, all of the second neighbours of the tile, all of the third neighbours of the tile etc)
	//method will loop untill path is found or all of the tiles are marked and end is not found
	while (!path_found)
	{
		num++;
		//iteration points is the list of tiles that will be marked in the next generation
		std::vector<constants::pathfinding_tile*> next_generation;
		//loop through all of the tiles from the current generation and add the returned neighbours to the next generation
		for (int i = 0; i < (int)cur_generation.size(); i++)
		{
			std::vector<constants::pathfinding_tile*> t1 = mark_tile_neighbours(cur_generation.at(i), num);
			for (int j = 0; j < (int)t1.size(); j++)
				next_generation.push_back(t1.at(j));
		}

		//store next generation as current generation
		cur_generation = next_generation;
		//if there is no more tiles in the next generation to be marked, stop looping
		if (next_generation.size() == 0)
		{
			/*if (origin.x != -1 && origin.y != -1)
				map[origin.x][origin.y]->pathfinding_num = -10;*/
			return;
		}
	}
	
	/*if (origin.x != -1 && origin.y != -1)
		map[start->position.x][start->position.y]->pathfinding_num = -10;*/
}

//function backtracks from the given end tile to the origin
bool LeePathfinder::calculate_path(constants::pathfinding_tile* end)
{
	constants::pathfinding_tile* cur_point = end;
	//path.push_back(endpoint);
	bool start_reached = false;
	if (map[end->position.y][end->position.x]->pathfinding_num == -1)
		return false;

	while (!start_reached)
	{
		constants::pathfinding_tile* min_point = cur_point->neighbours.at(0);
		int counter = 1;
		while (min_point->pathfinding_num == -1)
		{
			min_point = cur_point->neighbours.at(counter);
			counter++;
		}

		for (int i = 0; i < (int)cur_point->neighbours.size(); i++)
		{
			if (min_point->pathfinding_num > cur_point->neighbours.at(i)->pathfinding_num &&
				cur_point->neighbours.at(i)->pathfinding_num != 0 &&
				cur_point->neighbours.at(i)->pathfinding_num != -11 &&
				cur_point->neighbours.at(i)->pathfinding_num != -1)
				min_point = cur_point->neighbours.at(i);
		}

		constants::pathfinding_tile* temp = new constants::pathfinding_tile{ min_point->position.x, min_point->position.y, 3 };

		if (min_point->pathfinding_num == -10)
		{
			start_reached = true;
			path_found = true;
		}
		else
			path.push_back({ temp->position.x, temp->position.y });

		cur_point = min_point;
	}

	if(start_reached)
		return true;
}

bool LeePathfinder::find_path(SDL_Point end_coords)
{
	path.clear();
	return calculate_path(map[end_coords.y][end_coords.x]);
}

void LeePathfinder::set_origin(int x, int y)
{ 
	origin.x = x; 
	origin.y = y; 
	map[y][x]->pathfinding_num = -10;
}

void LeePathfinder::set_destination(int x, int y)
{
	origin.x = x;
	origin.y = y;
	map[y][x]->pathfinding_num = -11;
}

void LeePathfinder::display_field()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			std::cout << map[i][j]->pathfinding_num << ",";
		std::cout << std::endl;
	}
}

LeePathfinder::~LeePathfinder()
{
}


